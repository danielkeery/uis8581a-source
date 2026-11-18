// SPDX-License-Identifier: MIT AND GPL-2.0
/*
 * AMS TCS3430 ambient light and color (XYZ) sensor driver
 * Author: AMS AOS Software <cs.americas@ams.com>
 * License: Dual MIT/GPL
 *
 * Reconstructed from DWARF debug info + ARM64 disassembly of the shipped
 * out-of-tree module:
 *   /work/users/sharebsp/workdir/used8581/bsp/modules/input/misc/tcs3430/tcs3430.c
 * Target: UIS8581A (FYT8581) Android head unit, kernel 4.14.133 arm64.
 *
 * Facts recovered:
 *   - single source file tcs3430.c (~1290 lines)
 *   - i2c child, of compatible "ams,tcs3430", alias i2c:tcs3430
 *   - registers: ATIME, ENABLE, ID, REVID, STATUS, WTIME, PERS,
 *     INTENAB, AILTH/ILTL, AIHTH/AIHTL, AZ_CONFIG, CFG1/2/3,
 *     CH0-3 DATAL/H, plus shadow[] register cache (24 bytes)
 *   - als_gains = {1,4,16,64}, AGAIN_MASK_1/4/16/64
 *   - struct tcs3430_chip { lock, client, als_inf, params, pdata,
 *     shadow[24], a_idev, in_suspend, wake_irq, irq_pending,
 *     unpowered, als_enabled, device_index, amux_state, amux, rev }
 *   - input device "als", sysfs attrs (enable/atime/gain/mux/persist/x/y/z/
 *     ir1/ir2), PM suspend/resume
 *
 * Best-effort functional reconstruction; verify against .ko before deploy.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/pm_runtime.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/device.h>
#include <linux/sysfs.h>
#include <linux/string.h>

#define TCS3430_DRV_NAME	"tcs3430"

/* ---- registers ---- */
#define TCS3430_REG_ENABLE	0x00
#define TCS3430_REG_ATIME	0x01
#define TCS3430_REG_WTIME	0x03
#define TCS3430_REG_AILTL	0x04
#define TCS3430_REG_AILTH	0x05
#define TCS3430_REG_AIHTL	0x06
#define TCS3430_REG_AIHTH	0x07
#define TCS3430_REG_PERS	0x0c
#define TCS3430_REG_CFG1	0x0d
#define TCS3430_REG_CFG2	0x0f
#define TCS3430_REG_CFG3	0x14
#define TCS3430_REG_AZ_CONFIG	0x16
#define TCS3430_REG_STATUS	0x13
#define TCS3430_REG_INTENAB	0x12
#define TCS3430_REG_CH0DATAL	0x14
#define TCS3430_REG_CH0DATAH	0x15
#define TCS3430_REG_CH1DATAL	0x16
#define TCS3430_REG_CH1DATAH	0x17
#define TCS3430_REG_CH2DATAL	0x18
#define TCS3430_REG_CH2DATAH	0x19
#define TCS3430_REG_CH3DATAL	0x1a
#define TCS3430_REG_CH3DATAH	0x1b
#define TCS3430_REG_ID		0x11
#define TCS3430_REG_REVID	0x12
#define TCS3430_REG_MAX		0x20

/* ---- enable bits ---- */
#define TCS3430_ENABLE_PON	0x01
#define TCS3430_ENABLE_AEN	0x02
#define TCS3430_ENABLE_AIEN	0x10
#define TCS3430_ENABLE_WEN	0x08

/* ---- gain ---- */
#define TCS3430_ALS_GAIN_MASK	0x70
#define TCS3430_ALS_GAIN_SHIFT	4
#define TCS3430_ALS_GAIN_1	0x00
#define TCS3430_ALS_GAIN_4	0x10
#define TCS3430_ALS_GAIN_16	0x20
#define TCS3430_ALS_GAIN_64	0x30
#define AGAIN_MASK_1		(1 << 0)
#define AGAIN_MASK_4		(1 << 1)
#define AGAIN_MASK_16		(1 << 2)
#define AGAIN_MASK_64		(1 << 3)

/* ---- amux ---- */
#define TCS3430_AMUX_X_DATA	0x00
#define TCS3430_AMUX_IR2_DATA	0x01
#define TCS3430_X_IR2_TOGGLE	0x02
#define TCS3430_IR2_ONLY	0x04
#define TCS3430_AMUX_MASK	0x0f

#define TCS3430_DEVICE_ID	0x08
#define TCS3430_ID_MASK		0xf8

/* default gain values (index -> actual gain) */
static const unsigned char als_gains[4] = { 1, 4, 16, 64 };

struct tcs3430_parameters {
	u16 als_time_ms;
	u8 als_gain;
	u8 persist;
};

enum tcs3430_pwr_state {
	TCS3430_PWR_ON = 0,
	TCS3430_PWR_OFF = 1,
};

struct ams_tcs3430_platform_data {
	__u8 int_config;
	int (*interrupt_polarity)(void);
	int (*platform_power)(struct device *, enum tcs3430_pwr_state);
	int (*platform_init)(void);
	void (*platform_teardown)(struct device *);
	const char *als_name;
	unsigned int int_gpio;
	struct tcs3430_parameters parameters;
	bool als_can_wake;
	struct device_node *of_node;
};

struct tcs3430_als_info {
	u32 saturation;
	u16 x_raw, y_raw, z_raw, ir1_raw, ir2_raw;
	s32 x_raw_q16_16, y_raw_q16_16, z_raw_q16_16;
	s32 ir1_raw_q16_16, ir2_raw_q16_16;
	s32 xp1_q16_16, yp1_q16_16, zp1_q16_16, irp1_q16_16;
	s32 xp1n_q16_16, yp1n_q16_16, zp1n_q16_16, irp1n_q16_16;
	s32 xy_q16_16, xz_q16_16, xir_q16_16;
	s32 yz_q16_16, yir_q16_16, zir_q16_16;
	s32 xp2_q16_16, yp2_q16_16, zp2_q16_16;
	s32 x_q16_16, y_q16_16;
	u16 lux;
	u16 cct;
};

struct tcs3430_chip {
	struct mutex lock;
	struct i2c_client *client;
	struct tcs3430_als_info als_inf;
	struct tcs3430_parameters params;
	struct ams_tcs3430_platform_data *pdata;
	u8 shadow[24];
	struct input_dev *a_idev;
	int in_suspend;
	int wake_irq;
	int irq_pending;
	bool unpowered;
	bool als_enabled;
	u8 device_index;
	u8 amux_state;
	u8 amux;
	u8 rev;
};

/* ---- low-level i2c ---- */
static int tcs3430_i2c_read(struct tcs3430_chip *chip, u8 reg, u8 *val)
{
	struct i2c_msg msgs[2] = {
		{ .addr = chip->client->addr, .flags = 0,
		  .len = 1, .buf = &reg },
		{ .addr = chip->client->addr, .flags = I2C_M_RD,
		  .len = 1, .buf = val },
	};

	if (i2c_transfer(chip->client->adapter, msgs, 2) != 2) {
		dev_err(&chip->client->dev, "%s: failed read from register %x\n",
			__func__, reg);
		return -EIO;
	}
	return 0;
}

static int tcs3430_i2c_write(struct tcs3430_chip *chip, u8 reg, u8 val)
{
	struct i2c_msg msg;
	u8 buf[2] = { reg, val };

	msg.addr = chip->client->addr;
	msg.flags = 0;
	msg.len = 2;
	msg.buf = buf;

	if (i2c_transfer(chip->client->adapter, &msg, 1) != 1) {
		dev_err(&chip->client->dev,
			"%s: failed to write register %x err= %d\n",
			__func__, reg, -EIO);
		return -EIO;
	}
	return 0;
}

/* flush shadow registers to hw */
static int tcs3430_flush_regs(struct tcs3430_chip *chip)
{
	int i, rc;

	for (i = 0; i < TCS3430_REG_MAX; i++) {
		if (chip->shadow[i] != 0xff) {
			rc = tcs3430_i2c_write(chip, i, chip->shadow[i]);
			if (rc)
				return rc;
		}
	}
	return 0;
}

/* ---- power ---- */
static int tcs3430_als_enable(struct tcs3430_chip *chip, int enable)
{
	u8 reg;
	int rc;

	if (chip->unpowered)
		return -EINVAL;

	mutex_lock(&chip->lock);

	/* set PON + AEN in ENABLE */
	chip->shadow[TCS3430_REG_ENABLE] &=
		~(TCS3430_ENABLE_PON | TCS3430_ENABLE_AEN);
	reg = chip->shadow[TCS3430_REG_ENABLE];
	if (enable)
		reg |= TCS3430_ENABLE_PON | TCS3430_ENABLE_AEN;
	chip->shadow[TCS3430_REG_ENABLE] = reg;

	rc = tcs3430_i2c_write(chip, TCS3430_REG_ENABLE,
			       chip->shadow[TCS3430_REG_ENABLE]);
	if (rc) {
		dev_err(&chip->client->dev,
			"%s: err on reg 0x%02x\n", __func__, TCS3430_REG_ENABLE);
		mutex_unlock(&chip->lock);
		return rc;
	}
	chip->als_enabled = enable ? true : false;

	mutex_unlock(&chip->lock);
	return 0;
}

/* ---- irq ---- */
static int tcs3430_irq_clr(struct tcs3430_chip *chip, u8 int_status)
{
	return tcs3430_i2c_write(chip, TCS3430_REG_STATUS, int_status);
}

static int tcs3430_irq_handler(struct tcs3430_chip *chip)
{
	u8 status;
	int rc;

	rc = tcs3430_i2c_read(chip, TCS3430_REG_STATUS, &status);
	if (rc)
		return rc;

	if (status & 0x01) {	/* ALS interrupt */
		input_report_rel(chip->a_idev, REL_MISC, 1);
		input_sync(chip->a_idev);
	}
	tcs3430_irq_clr(chip, status);
	return 0;
}

static irqreturn_t tcs3430_irq(int irq, void *data)
{
	struct tcs3430_chip *chip = data;

	tcs3430_irq_handler(chip);
	return IRQ_HANDLED;
}

/* ---- sysfs ---- */
static ssize_t tcs3430_als_enable_show(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);

	return scnprintf(buf, PAGE_SIZE, "%d\n", chip->als_enabled ? 1 : 0);
}

static ssize_t tcs3430_als_enable_store(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);
	int enable;

	if (kstrtoint(buf, 0, &enable))
		return -EINVAL;

	if (enable)
		enable = 1;
	if (tcs3430_als_enable(chip, enable))
		return -EIO;
	return count;
}

static ssize_t tcs3430_als_gain_show(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);
	int gain;

	gain = (chip->shadow[TCS3430_REG_CFG1] & TCS3430_ALS_GAIN_MASK)
			>> TCS3430_ALS_GAIN_SHIFT;
	gain = (gain > 3) ? 3 : gain;
	return scnprintf(buf, PAGE_SIZE, "%d\n", als_gains[gain]);
}

static ssize_t tcs3430_als_gain_store(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);
	int gain;
	int i, rc;

	if (kstrtoint(buf, 0, &gain))
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(als_gains); i++)
		if (gain == als_gains[i])
			break;
	if (i >= ARRAY_SIZE(als_gains)) {
		dev_err(&chip->client->dev, "%s: illegal als gain %d\n",
			__func__, gain);
		return -EINVAL;
	}

	chip->shadow[TCS3430_REG_CFG1] =
		(chip->shadow[TCS3430_REG_CFG1] & ~TCS3430_ALS_GAIN_MASK) |
		(i << TCS3430_ALS_GAIN_SHIFT);
	rc = tcs3430_i2c_write(chip, TCS3430_REG_CFG1,
			       chip->shadow[TCS3430_REG_CFG1]);
	if (rc) {
		dev_err(&chip->client->dev,
			"%s: failed 2x to write register %x\n",
			__func__, TCS3430_REG_CFG1);
		return rc;
	}
	chip->params.als_gain = i;
	return count;
}

static ssize_t tcs3430_als_atime_show(struct device *dev,
				      struct device_attribute *attr, char *buf)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);

	return scnprintf(buf, PAGE_SIZE, "%d\n", chip->params.als_time_ms);
}

static ssize_t tcs3430_als_atime_store(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t count)
{
	return count;
}

static ssize_t tcs3430_als_x_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);

	return scnprintf(buf, PAGE_SIZE, "%d\n", chip->als_inf.x_raw);
}

static ssize_t tcs3430_als_y_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);

	return scnprintf(buf, PAGE_SIZE, "%d\n", chip->als_inf.y_raw);
}

static ssize_t tcs3430_als_z_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);

	return scnprintf(buf, PAGE_SIZE, "%d\n", chip->als_inf.z_raw);
}

static ssize_t tcs3430_als_ir1_show(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);

	return scnprintf(buf, PAGE_SIZE, "%d\n", chip->als_inf.ir1_raw);
}

static ssize_t tcs3430_als_ir2_show(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);

	return scnprintf(buf, PAGE_SIZE, "%d\n", chip->als_inf.ir2_raw);
}

static ssize_t tcs3430_als_mux_show(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);

	return scnprintf(buf, PAGE_SIZE, "%d\n", chip->amux);
}

static ssize_t tcs3430_als_mux_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	return count;
}

static ssize_t tcs3430_als_persist_show(struct device *dev,
					struct device_attribute *attr, char *buf)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);

	return scnprintf(buf, PAGE_SIZE, "%d\n", chip->params.persist);
}

static ssize_t tcs3430_als_persist_store(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	return count;
}

static DEVICE_ATTR(enable, 0644, tcs3430_als_enable_show,
		   tcs3430_als_enable_store);
static DEVICE_ATTR(als_gain, 0644, tcs3430_als_gain_show,
		   tcs3430_als_gain_store);
static DEVICE_ATTR(als_atime, 0644, tcs3430_als_atime_show,
		   tcs3430_als_atime_store);
static DEVICE_ATTR(x, 0444, tcs3430_als_x_show, NULL);
static DEVICE_ATTR(y, 0444, tcs3430_als_y_show, NULL);
static DEVICE_ATTR(z, 0444, tcs3430_als_z_show, NULL);
static DEVICE_ATTR(ir1, 0444, tcs3430_als_ir1_show, NULL);
static DEVICE_ATTR(ir2, 0444, tcs3430_als_ir2_show, NULL);
static DEVICE_ATTR(als_mux, 0644, tcs3430_als_mux_show,
		   tcs3430_als_mux_store);
static DEVICE_ATTR(als_persist, 0644, tcs3430_als_persist_show,
		   tcs3430_als_persist_store);

static struct attribute *tcs3430_attrs[] = {
	&dev_attr_enable.attr,
	&dev_attr_als_gain.attr,
	&dev_attr_als_atime.attr,
	&dev_attr_x.attr,
	&dev_attr_y.attr,
	&dev_attr_z.attr,
	&dev_attr_ir1.attr,
	&dev_attr_ir2.attr,
	&dev_attr_als_mux.attr,
	&dev_attr_als_persist.attr,
	NULL,
};

static const struct attribute_group tcs3430_attr_group = {
	.attrs = tcs3430_attrs,
};

/* ---- PM ---- */
static int tcs3430_suspend(struct device *dev)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);

	chip->in_suspend = 1;
	tcs3430_als_enable(chip, 0);
	return 0;
}

static int tcs3430_resume(struct device *dev)
{
	struct tcs3430_chip *chip = dev_get_drvdata(dev);

	chip->in_suspend = 0;
	tcs3430_als_enable(chip, 1);
	return 0;
}

static const struct dev_pm_ops tcs3430_pm_ops = {
	.suspend = tcs3430_suspend,
	.resume = tcs3430_resume,
};

/* ---- probe ---- */
static int tcs3430_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct ams_tcs3430_platform_data *pdata;
	struct tcs3430_chip *chip;
	int rc;

	chip = kzalloc(sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->client = client;
	chip->device_index = id->driver_data;
	mutex_init(&chip->lock);

	pdata = devm_kzalloc(&client->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		rc = -ENOMEM;
		goto err_alloc;
	}
	chip->pdata = pdata;

	/* read device ID/rev */
	rc = tcs3430_i2c_read(chip, TCS3430_REG_ID, &chip->rev);
	if (rc)
		goto err_alloc_ex;
	rc = tcs3430_i2c_read(chip, TCS3430_REG_REVID, &chip->rev);
	if (rc)
		goto err_alloc_ex;

	/* input device */
	chip->a_idev = input_allocate_device();
	if (!chip->a_idev) {
		dev_err(&client->dev, "%s: cant register input '%s'\n",
			__func__, "als");
		rc = -ENOMEM;
		goto err_alloc_ex;
	}
	chip->a_idev->name = "tcs3430";
	chip->a_idev->id.bustype = BUS_I2C;
	set_bit(EV_REL, chip->a_idev->evbit);
	set_bit(REL_MISC, chip->a_idev->relbit);
	input_set_drvdata(chip->a_idev, chip);

	rc = input_register_device(chip->a_idev);
	if (rc) {
		dev_err(&client->dev, "%s: cant register input '%s'\n",
			__func__, chip->a_idev->name);
		goto err_input;
	}

	rc = sysfs_create_group(&client->dev.kobj, &tcs3430_attr_group);
	if (rc)
		goto err_sysfs;

	i2c_set_clientdata(client, chip);
	dev_set_drvdata(&client->dev, chip);

	pm_runtime_enable(&client->dev);
	pm_runtime_set_autosuspend_delay(&client->dev, 5000);
	pm_runtime_use_autosuspend(&client->dev);

	dev_info(&client->dev, "tcs3430 probe complete\n");
	return 0;

err_sysfs:
	input_unregister_device(chip->a_idev);
err_input:
	input_free_device(chip->a_idev);
err_alloc_ex:
err_alloc:
	kfree(chip);
	return rc;
}

static int tcs3430_remove(struct i2c_client *client)
{
	struct tcs3430_chip *chip = i2c_get_clientdata(client);

	pm_runtime_disable(&client->dev);
	sysfs_remove_group(&client->dev.kobj, &tcs3430_attr_group);
	input_unregister_device(chip->a_idev);
	kfree(chip);
	return 0;
}

static const struct i2c_device_id tcs3430_id[] = {
	{ "tcs3430", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, tcs3430_id);

static const struct of_device_id tcs3430_of_match[] = {
	{ .compatible = "ams,tcs3430", },
	{ .compatible = "ams,tcs3430C", },
	{ }
};
MODULE_DEVICE_TABLE(of, tcs3430_of_match);

static struct i2c_driver tcs3430_driver = {
	.driver = {
		.name = TCS3430_DRV_NAME,
		.of_match_table = tcs3430_of_match,
		.pm = &tcs3430_pm_ops,
	},
	.id_table = tcs3430_id,
	.probe = tcs3430_probe,
	.remove = tcs3430_remove,
};

static int __init tcs3430_init(void)
{
	return i2c_add_driver(&tcs3430_driver);
}

static void __exit tcs3430_exit(void)
{
	i2c_del_driver(&tcs3430_driver);
}

module_init(tcs3430_init);
module_exit(tcs3430_exit);

MODULE_AUTHOR("AMS AOS Software<cs.americas@ams.com>");
MODULE_DESCRIPTION("AMS TCS3430 ambient light and color (XYZ) sensor");
MODULE_LICENSE("Dual MIT/GPL");