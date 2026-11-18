// SPDX-License-Identifier: GPL-2.0
/*
 * LTR-308ALS ambient light sensor driver
 * Author: Lite-On Technology Corp   License: GPL   v1.00
 *
 * Reconstructed from DWARF debug info + ARM64 disassembly of the shipped
 * out-of-tree module:
 *   /work/users/sharebsp/workdir/used8581/bsp/modules/input/misc/ltr308als/ltr_308als.c
 * Target: UIS8581A (FYT8581) Android head unit, kernel 4.14.133 arm64.
 *
 * Source facts recovered:
 *   - single source file, 1880+ lines
 *   - global instance: static struct ltr308ALS_data *sensor_info
 *   - i2c child on bus 0x705 (i2c0) @ 0x53, "ltr308als"
 *   - register map: ALS_CONTR=0x80, MEAS_RES=0x81, GAIN=0x82,
 *     MEAS_RATE=0x85, INTERRUPT=0x86, PART_ID=0x86, THDL=0x8e, THDH=0x92
 *   - 1-wire I2C read (reg addr byte + data), i2c_transfer 2 msgs
 *   - input device ABS_MISC + sysfs attributes + miscdevice "ltr_308als"
 *   - ADF panel suspend/resume notifier
 *
 * This is a best-effort functional reconstruction for rebuild/porting.
 * Verify against the .ko before deploying.
 */

#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/input.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/sysfs.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/of.h>

/* ---- register map ---- */
#define LTR308ALS_REG_ALS_CONTR	0x80
#define LTR308ALS_REG_ALS_MEAS_RES	0x81
#define LTR308ALS_REG_ALS_GAIN	0x82
#define LTR308ALS_REG_ALS_MEAS_RATE	0x85
#define LTR308ALS_REG_ALS_INTERRUPT	0x86
#define LTR308ALS_REG_ALS_PART_ID	0x86
#define LTR308ALS_REG_ALS_DATA_0	0x88
#define LTR308ALS_REG_ALS_DATA_1	0x89
#define LTR308ALS_REG_ALS_DATA_2	0x8a
#define LTR308ALS_REG_ALS_DATA_3	0x8b
#define LTR308ALS_REG_ALS_STATUS	0x8c
#define LTR308ALS_REG_ALS_THDL	0x8e
#define LTR308ALS_REG_ALS_THDH	0x92

#define ALS_CONTR_SW_RESET	0x04
#define ALS_CONTR_ENABLE	0x01
#define ALS_CONTR_ACTIVE	0x80
#define ALS_GAIN_MASK		0xf8
#define ALS_MEAS_RATE_MASK	0x0f

#define LTR308ALS_PART_ID_EXP	0x0e

/* ADF panel events */
#define ADF_EVENT_ENABLE	0x1
#define ADF_EVENT_DISABLE	0x0

struct ltr308ALS_data {
	struct i2c_client *i2c_client;
	struct input_dev *als_input_dev;
	struct workqueue_struct *workqueue;
	uint8_t als_enable_flag;
	uint8_t als_irq_flag;
	uint8_t als_opened;
	uint8_t als_log;
	int irq;
	int gpio_int_no;
	int is_suspend;
	bool enabled;
	struct notifier_block adf_event;
	struct work_struct adf_work;
};

static struct ltr308ALS_data *sensor_info;

static int ltr308ALS_panel_notify(struct notifier_block *nb,
				  unsigned long event, void *data);
static int ltr308_adf_init(struct ltr308ALS_data *d);
static int ltr308_adf_deinit(struct ltr308ALS_data *d);
static uint32_t als_adc_read(void);

/* ---- low-level i2c ---- */
static int8_t I2C_Read(uint8_t *buf, uint8_t count)
{
	struct i2c_msg msgs[2];
	int ret;

	msgs[0].addr = sensor_info->i2c_client->addr;
	msgs[0].flags = 0;
	msgs[0].len = 1;
	msgs[0].buf = &buf[0];

	msgs[1].addr = sensor_info->i2c_client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = count;
	msgs[1].buf = &buf[1];

	ret = i2c_transfer(sensor_info->i2c_client->adapter, msgs, 2);
	if (ret != 2) {
		pr_err("1%s I2C Read Fail !!!!\n", __func__);
		return -1;
	}
	return 0;
}

static int8_t I2C_Write(uint8_t *buf, uint8_t count)
{
	struct i2c_msg msgs[1];
	int ret;

	msgs[0].addr = sensor_info->i2c_client->addr;
	msgs[0].flags = 0;
	msgs[0].len = count;
	msgs[0].buf = buf;

	ret = i2c_transfer(sensor_info->i2c_client->adapter, msgs, 1);
	if (ret != 1) {
		pr_err("1%s I2C Write Fail !!!!\n", __func__);
		return -1;
	}
	return 0;
}

/* ---- readbacks ---- */
static int8_t ls_en_readback(uint8_t *buf, struct ltr308ALS_data *d)
{
	buf[0] = LTR308ALS_REG_ALS_CONTR;
	return I2C_Read(buf, 1);
}

static int8_t ls_thr_readback(uint32_t *lo_thr, uint32_t *hi_thr,
			       struct ltr308ALS_data *d)
{
	uint8_t buf[5];

	buf[0] = LTR308ALS_REG_ALS_THDL;
	if (I2C_Read(buf, 4))
		return -1;
	*lo_thr = ((uint32_t)buf[1] << 8) | buf[2];
	*hi_thr = ((uint32_t)buf[3] << 8) | buf[4];
	return 0;
}

static int8_t ls_gain_readback(uint8_t *buf, struct ltr308ALS_data *d)
{
	buf[0] = LTR308ALS_REG_ALS_GAIN;
	return I2C_Read(buf, 1);
}

static int8_t ls_reso_readback(uint8_t *buf, struct ltr308ALS_data *d)
{
	buf[0] = LTR308ALS_REG_ALS_MEAS_RES;
	return I2C_Read(buf, 1);
}

/* ---- setters ---- */
static int8_t set_ls_interrupt(uint8_t lo_thr, uint8_t hi_thr,
				struct ltr308ALS_data *d)
{
	uint8_t buf[4];

	buf[0] = LTR308ALS_REG_ALS_THDL;
	buf[1] = lo_thr;
	buf[2] = lo_thr >> 8;
	buf[3] = 0;
	if (I2C_Write(buf, 4))
		return -1;
	buf[0] = LTR308ALS_REG_ALS_THDH;
	buf[1] = hi_thr;
	buf[2] = hi_thr >> 8;
	buf[3] = 0;
	if (I2C_Write(buf, 4))
		return -1;
	buf[0] = LTR308ALS_REG_ALS_INTERRUPT;
	buf[1] = 0x02;
	buf[2] = 0;
	if (I2C_Write(buf, 3))
		return -1;
	return 0;
}

static int8_t set_ls_en(uint8_t enable, struct ltr308ALS_data *d)
{
	uint8_t buf[2];

	buf[0] = LTR308ALS_REG_ALS_CONTR;
	if (I2C_Read(buf, 1))
		return -1;
	buf[1] = enable ? (buf[1] | ALS_CONTR_ENABLE | ALS_CONTR_ACTIVE)
		       : (buf[1] & ~ALS_CONTR_ENABLE);
	return I2C_Write(buf, 2);
}

static int8_t set_ls_meas_rate(uint8_t rate, struct ltr308ALS_data *d)
{
	uint8_t buf[2];

	buf[0] = LTR308ALS_REG_ALS_MEAS_RATE;
	if (I2C_Read(buf, 1))
		return -1;
	buf[1] = (buf[1] & ~ALS_MEAS_RATE_MASK) | (rate & ALS_MEAS_RATE_MASK);
	return I2C_Write(buf, 2);
}

static int8_t set_ls_gain(uint8_t gain, struct ltr308ALS_data *d)
{
	uint8_t buf[2];

	buf[0] = LTR308ALS_REG_ALS_GAIN;
	if (I2C_Read(buf, 1))
		return -1;
	buf[1] = (buf[1] & ~ALS_GAIN_MASK) | gain;
	return I2C_Write(buf, 2);
}

static int8_t set_ls_reso(uint8_t reso, struct ltr308ALS_data *d)
{
	uint8_t buf[2];

	buf[0] = LTR308ALS_REG_ALS_MEAS_RES;
	if (I2C_Read(buf, 1))
		return -1;
	buf[1] = (buf[1] & ~0x0f) | (reso & 0x0f);
	return I2C_Write(buf, 2);
}

/* ---- enable/disable ---- */
static int8_t als_enable_withint(struct ltr308ALS_data *d)
{
	uint8_t buf[2];

	if (d->als_enable_flag) {
		pr_info("%s: ALS already enabled...\n", __func__);
		return 0;
	}
	if (set_ls_meas_rate(0x04, d)) {
		pr_info("%s: ALS_Meas_Rate register Setup Fail...\n", __func__);
		return -1;
	}
	if (set_ls_reso(0x00, d)) {
		pr_info("%s: ALS resolution setup Fail...\n", __func__);
		return -1;
	}
	if (set_ls_gain(0x00, d)) {
		pr_info("%s: ALS gain setup Fail...\n", __func__);
		return -1;
	}
	buf[0] = LTR308ALS_REG_ALS_CONTR;
	buf[1] = ALS_CONTR_ENABLE | ALS_CONTR_ACTIVE;
	if (I2C_Write(buf, 2)) {
		pr_info("%s: ALS enable Fail...\n", __func__);
		return -1;
	}
	d->als_enable_flag = 1;
	return 0;
}

static int8_t als_disable(struct ltr308ALS_data *d)
{
	uint8_t buf[2];

	if (!d->als_enable_flag) {
		pr_info("%s: ALS already disabled...\n", __func__);
		return 0;
	}
	buf[0] = LTR308ALS_REG_ALS_CONTR;
	if (I2C_Read(buf, 1))
		return -1;
	buf[1] &= ~ALS_CONTR_ENABLE;
	if (I2C_Write(buf, 2)) {
		pr_info("%s: LS disable Fail...\n", __func__);
		return -1;
	}
	d->als_enable_flag = 0;
	return 0;
}

/* ---- file ops ---- */
static int als_open(struct inode *inode, struct file *file)
{
	if (sensor_info->als_opened) {
		pr_info("%s: ALS already Opened...\n", __func__);
		return -1;
	}
	sensor_info->als_opened = 1;
	return 0;
}

static int als_release(struct inode *inode, struct file *file)
{
	sensor_info->als_opened = 0;
	return 0;
}

static long als_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int value = 0;

	pr_info("%s cmd %d\n", __func__, cmd);
	switch (cmd) {
	case 0x01:
		value = 1;
		break;
	case 0x02:
		value = 0;
		break;
	case 0x03:
		value = sensor_info->als_enable_flag;
		break;
	default:
		pr_info("3%s: INVALID COMMAND %d\n", __func__, cmd);
		return -1;
	}
	pr_info("%s value = %d\n", __func__, value);
	return value;
}

static long ltr308_misc_ioctl_compat(struct file *file, unsigned int cmd,
				     unsigned long arg)
{
	return als_ioctl(file, cmd, arg);
}

static const struct file_operations als_fops = {
	.owner = THIS_MODULE,
	.open = als_open,
	.release = als_release,
	.unlocked_ioctl = als_ioctl,
	.compat_ioctl = ltr308_misc_ioctl_compat,
};

static struct miscdevice als_misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "ltr_308als",
	.fops = &als_fops,
};

/* ---- sysfs ---- */
static ssize_t als_adc_show(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	uint8_t data[5];
	uint32_t val;

	val = als_adc_read();
	return sprintf(buf, "%u\n", val);
}

static uint32_t als_adc_read(void)
{
	uint8_t data[5];
	uint32_t val;

	data[0] = LTR308ALS_REG_ALS_DATA_0;
	if (I2C_Read(data, 4))
		return 0;
	val = ((uint32_t)data[4] << 24) | (data[3] << 16) |
	      (data[2] << 8) | data[1];
	return val;
}

static ssize_t ls_en_show(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	return sprintf(buf, "%d\n", sensor_info->als_enable_flag);
}

static ssize_t ls_en_store(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	int value;

	if (sscanf(buf, "%d", &value) != 1)
		return -EINVAL;
	if (value)
		als_enable_withint(sensor_info);
	else
		als_disable(sensor_info);
	return count;
}

static ssize_t ls_lo_thr_show(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	uint32_t lo, hi;

	if (ls_thr_readback(&lo, &hi, sensor_info))
		return -EIO;
	return sprintf(buf, "0x%x\n", lo);
}

static ssize_t ls_hi_thr_show(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	uint32_t lo, hi;

	if (ls_thr_readback(&lo, &hi, sensor_info))
		return -EIO;
	return sprintf(buf, "0x%x\n", hi);
}

static ssize_t ls_gain_show(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	uint8_t data[2];

	if (ls_gain_readback(data, sensor_info))
		return -EIO;
	return sprintf(buf, "0x%x\n", data[1]);
}

static ssize_t ls_gain_store(struct device *dev, struct device_attribute *attr,
			     const char *buf, size_t count)
{
	unsigned int value;

	if (sscanf(buf, "%x", &value) != 1)
		return -EINVAL;
	if (set_ls_gain(value, sensor_info))
		return -EIO;
	return count;
}

static ssize_t ls_reso_show(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	uint8_t data[2];

	if (ls_reso_readback(data, sensor_info))
		return -EIO;
	return sprintf(buf, "0x%x\n", data[1]);
}

static ssize_t ls_reso_store(struct device *dev, struct device_attribute *attr,
			     const char *buf, size_t count)
{
	unsigned int value;

	if (sscanf(buf, "%x", &value) != 1)
		return -EINVAL;
	if (set_ls_reso(value, sensor_info))
		return -EIO;
	return count;
}

static ssize_t ls_debug_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	return sprintf(buf, "0x%x\n", sensor_info->als_enable_flag);
}

static ssize_t ls_debug_store(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	return count;
}

static DEVICE_ATTR_RO(als_adc);
static DEVICE_ATTR_RW(ls_en);
static DEVICE_ATTR_RO(ls_lo_thr);
static DEVICE_ATTR_RO(ls_hi_thr);
static DEVICE_ATTR_RW(ls_gain);
static DEVICE_ATTR_RW(ls_reso);
static DEVICE_ATTR_RO(ls_debug);

static struct attribute *als_attributes[] = {
	&dev_attr_als_adc.attr,
	&dev_attr_ls_en.attr,
	&dev_attr_ls_lo_thr.attr,
	&dev_attr_ls_hi_thr.attr,
	&dev_attr_ls_gain.attr,
	&dev_attr_ls_reso.attr,
	&dev_attr_ls_debug.attr,
	NULL,
};

static const struct attribute_group als_attribute_group = {
	.attrs = als_attributes,
};

/* ---- workqueue + irq ---- */
static void ltr308ALS_schedwork(struct work_struct *work)
{
	input_report_abs(sensor_info->als_input_dev, ABS_MISC, als_adc_read());
	input_sync(sensor_info->als_input_dev);
}

static irqreturn_t ltr308ALS_irq_handler(int irq, void *dev_id)
{
	queue_work(sensor_info->workqueue, &sensor_info->adf_work);
	return IRQ_HANDLED;
}

/* ---- part id ---- */
static uint8_t _check_part_id(struct ltr308ALS_data *d)
{
	uint8_t buf[2];

	buf[0] = LTR308ALS_REG_ALS_PART_ID;
	if (I2C_Read(buf, 1))
		return 0xff;
	pr_info("%s %x\n", __func__, buf[1]);
	if (buf[1] != LTR308ALS_PART_ID_EXP) {
		pr_info("%s: Part failure miscompare act:0x%02x exp:0x%02x\n",
			__func__, buf[1], LTR308ALS_PART_ID_EXP);
		return 1;
	}
	return 0;
}

/* ---- probe ---- */
static int ltr308ALS_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct ltr308ALS_data *d;
	int err;

	d = devm_kzalloc(&client->dev, sizeof(*d), GFP_KERNEL);
	if (!d) {
		pr_info("%s: Mem Alloc Fail...\n", __func__);
		return -ENOMEM;
	}
	d->i2c_client = client;
	sensor_info = d;
	i2c_set_clientdata(client, d);

	if (_check_part_id(d)) {
		pr_info("%s: ALS Setup Fail...\n", __func__);
		return -ENODEV;
	}

	d->workqueue = create_singlethread_workqueue("ltr308ALS_wq");
	if (!d->workqueue) {
		pr_info("%s: Create WorkQueue Fail...\n", __func__);
		return -ENOMEM;
	}
	INIT_WORK(&d->adf_work, ltr308ALS_schedwork);

	d->als_input_dev = input_allocate_device();
	if (!d->als_input_dev) {
		pr_info("%s: ALS Input Allocate Device Fail...\n", __func__);
		err = -ENOMEM;
		goto err_input;
	}
	d->als_input_dev->name = "LTR308ALS";
	set_bit(EV_ABS, d->als_input_dev->evbit);
	input_set_abs_params(d->als_input_dev, ABS_MISC, 0, 65535, 0, 0);
	err = input_register_device(d->als_input_dev);
	if (err) {
		pr_info("%s: ALS Register Input Device Fail...\n", __func__);
		goto err_input;
	}

	err = sysfs_create_group(&client->dev.kobj, &als_attribute_group);
	if (err)
		goto err_sysfs;

	err = misc_register(&als_misc);
	if (err)
		goto err_misc;

	err = ltr308_adf_init(d);
	if (err) {
		pr_info("bh1750_adf_init fail!\n");
		goto err_adf;
	}

	pr_info("%s: probe complete\n", __func__);
	return 0;

err_adf:
	misc_deregister(&als_misc);
err_misc:
	sysfs_remove_group(&client->dev.kobj, &als_attribute_group);
err_sysfs:
	input_unregister_device(d->als_input_dev);
err_input:
	destroy_workqueue(d->workqueue);
	return err;
}

static int ltr308_remove(struct i2c_client *client)
{
	struct ltr308ALS_data *d = i2c_get_clientdata(client);

	ltr308_adf_deinit(d);
	misc_deregister(&als_misc);
	sysfs_remove_group(&client->dev.kobj, &als_attribute_group);
	input_unregister_device(d->als_input_dev);
	destroy_workqueue(d->workqueue);
	sensor_info = NULL;
	return 0;
}

/* ---- ADF panel suspend/resume ---- */
static int ltr308_adf_event_handler(struct notifier_block *nb,
				    unsigned long event, void *data)
{
	struct ltr308ALS_data *d =
		container_of(nb, struct ltr308ALS_data, adf_event);

	if (event == ADF_EVENT_DISABLE) {
		pr_info("ltr308 suspend\n");
		disable_irq_nosync(d->irq);
		d->is_suspend = 1;
		als_disable(d);
	} else if (event == ADF_EVENT_ENABLE) {
		pr_info("ltr308 resume\n");
		enable_irq(d->irq);
		d->is_suspend = 0;
		als_enable_withint(d);
	}
	return NOTIFY_OK;
}

static int ltr308ALS_panel_notify(struct notifier_block *nb,
				  unsigned long event, void *data)
{
	return ltr308_adf_event_handler(nb, event, data);
}

static int ltr308_adf_init(struct ltr308ALS_data *d)
{
	/* register with lsec panel notifier chain (lsec_panel_register) */
	return 0;
}

static int ltr308_adf_deinit(struct ltr308ALS_data *d)
{
	return 0;
}

/* ---- i2c driver ---- */
static const struct i2c_device_id ltr308ALS_id[] = {
	{ "ltr308als", 0 },
	{ },
};
MODULE_DEVICE_TABLE(i2c, ltr308ALS_id);

static const struct of_device_id ltr308_of_match[] = {
	{ .compatible = "ltr,ltr308als", },
	{ },
};
MODULE_DEVICE_TABLE(of, ltr308_of_match);

static struct i2c_driver ltr308ALS_driver = {
	.driver = {
		.name = "ltr308als",
		.of_match_table = ltr308_of_match,
	},
	.id_table = ltr308ALS_id,
	.probe = ltr308ALS_probe,
	.remove = ltr308_remove,
};

static int __init ltr308ALS_init(void)
{
	return i2c_add_driver(&ltr308ALS_driver);
}

static void __exit ltr308ALS_exit(void)
{
	i2c_del_driver(&ltr308ALS_driver);
}

module_init(ltr308ALS_init);
module_exit(ltr308ALS_exit);

MODULE_AUTHOR("Lite-On Technology Corp");
MODULE_DESCRIPTION("LTR-308ALS Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.00");