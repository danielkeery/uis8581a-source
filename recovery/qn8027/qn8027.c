// SPDX-License-Identifier: GPL-2.0
/*
 * QN8027 FM transmitter driver
 * Author: wusheng <sheng.wu@ls-ec.com>   License: GPL   version v0.0
 *
 * Reconstructed from DWARF debug info + ARM64 disassembly of the shipped
 * out-of-tree module:
 *   /work/users/sharebsp/workdir/used8581/bsp/modules/radio/FMtransmitter/qn8027.c
 * Target: UIS8581A (FYT8581) Android head unit, kernel 4.14.133 arm64.
 *
 * Facts recovered:
 *   - single source file qn8027.c (~1100 lines)
 *   - i2c child on i2c4 @ 0x2c, compatible "lsec,qn8027"
 *   - struct qn8027_i2c_data { client, dev, lock, freq, start, regvga,
 *     is_suspend, adf_event, txpa, txpower }
 *   - struct qn8027_reg { regval, dft, state }
 *   - sysfs: setfreq, volume, txpa, txpower, audio_mute, impendance
 *   - i2c regs: volume@0x02, txpa@0x04/0x05, 0x0c (channel), 0x10
 *   - misc device + ADF panel suspend/resume + lsec panel register
 *
 * Best-effort functional reconstruction; verify against .ko before deploy.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/sysfs.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/uaccess.h>

typedef unsigned char UINT8;
typedef unsigned short UINT16;

#define QN8027_DRV_NAME	"qn8027"

/* ---- register map ---- */
#define QN8027_REG_VOLUME	0x02
#define QN8027_REG_MUTE	0x04
#define QN8027_REG_TXPA	0x04
#define QN8027_REG_TXPOWER	0x05
#define QN8027_REG_CHANNEL	0x0c
#define QN8027_REG_STATUS	0x10
#define QN8027_REG_TRANSFER	0x30

/* command bits */
#define QN8027_MUTE_BIT	0x10
#define QN8027_VOLUME_MASK	0x0f
#define QN8027_TXPA_MASK	0x3f
#define QN8027_TXPOWER_MASK	0x7f
#define QN8027_CHANNEL_MASK	0x3f
#define QN8027_CHANNEL_SHIFT	2

struct qn8027_reg {
	unsigned char regval;
	unsigned char dft;
	unsigned short state;
};

struct qn8027_i2c_data {
	struct i2c_client *client;
	struct device *dev;
	struct mutex lock;
	int freq;
	char start;
	struct qn8027_reg regvga;
	int is_suspend;
	struct notifier_block adf_event;
	struct qn8027_reg txpa;
	unsigned char txpower;
};

static struct qn8027_i2c_data *qn8027_data;
static int qn8027_suspend(struct qn8027_i2c_data *data);
static int qn8027_resume(struct qn8027_i2c_data *data);
static UINT8 QNF_SetCh(struct qn8027_i2c_data *data, UINT16 freq);

/* ---- low-level i2c ---- */
static unsigned char qn8027_i2c_read(struct i2c_client *client,
				     unsigned char reg)
{
	struct i2c_msg msg[2];
	unsigned char buf[2];
	int ret;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf = &buf[0];
	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = 1;
	msg[1].buf = &buf[1];

	buf[0] = reg;
	ret = i2c_transfer(client->adapter, msg, 2);
	if (ret != 2) {
		pr_info("<<QN8027_INFO>>[%s:%d] i2c read fail retry %d \n",
			__func__, __LINE__, ret);
		return 0xff;
	}
	return buf[1];
}

static UINT8 qn8027_i2c_write(struct i2c_client *client, unsigned char reg,
			      unsigned char value)
{
	struct i2c_msg msg;
	unsigned char buf[2];
	int ret;

	buf[0] = reg;
	buf[1] = value;

	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = 2;
	msg.buf = buf;

	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret != 1) {
		pr_info("<<QN8027_INFO>>[%s:%d] i2c write fail retry\n",
			__func__, __LINE__);
		return 1;
	}
	return 0;
}

/* ---- FM control ---- */
void fm_set_volume(struct qn8027_i2c_data *data, unsigned char volume)
{
	unsigned char regval;

	regval = qn8027_i2c_read(data->client, QN8027_REG_VOLUME);
	regval &= ~QN8027_VOLUME_MASK;
	regval |= (volume & QN8027_VOLUME_MASK);
	qn8027_i2c_write(data->client, QN8027_REG_VOLUME, regval);
}

unsigned char fm_get_volume(struct qn8027_i2c_data *data)
{
	return qn8027_i2c_read(data->client, QN8027_REG_VOLUME) &
		QN8027_VOLUME_MASK;
}

void fm_set_audio_mute(struct qn8027_i2c_data *data, int mute)
{
	unsigned char regval;

	regval = qn8027_i2c_read(data->client, QN8027_REG_MUTE);
	if (mute)
		regval |= QN8027_MUTE_BIT;
	else
		regval &= ~QN8027_MUTE_BIT;
	qn8027_i2c_write(data->client, QN8027_REG_MUTE, regval);
}

int fm_get_audio_mute(struct qn8027_i2c_data *data)
{
	unsigned char regval;

	regval = qn8027_i2c_read(data->client, QN8027_REG_MUTE);
	return (regval & QN8027_MUTE_BIT) ? 1 : 0;
}

void fm_set_txpa(struct qn8027_i2c_data *data, unsigned char txpa)
{
	unsigned char regval;

	regval = qn8027_i2c_read(data->client, QN8027_REG_TXPA);
	regval &= ~QN8027_TXPA_MASK;
	regval |= (txpa & QN8027_TXPA_MASK);
	qn8027_i2c_write(data->client, QN8027_REG_TXPA, regval);
}

unsigned char fm_get_txpa(struct qn8027_i2c_data *data)
{
	return qn8027_i2c_read(data->client, QN8027_REG_TXPA) &
		QN8027_TXPA_MASK;
}

void fm_set_txpower(struct qn8027_i2c_data *data, unsigned char power)
{
	qn8027_i2c_write(data->client, QN8027_REG_TXPOWER, power);
}

unsigned char fm_get_txpower(struct qn8027_i2c_data *data)
{
	return qn8027_i2c_read(data->client, QN8027_REG_TXPOWER) &
		QN8027_TXPOWER_MASK;
}

void fm_set_impendance(struct qn8027_i2c_data *data, unsigned char imp)
{
	qn8027_i2c_write(data->client, 0x06, imp);
}

unsigned char fm_get_impendance(struct qn8027_i2c_data *data)
{
	return qn8027_i2c_read(data->client, 0x06);
}

void fm_set_transfer_rate(struct qn8027_i2c_data *data, int rate)
{
	qn8027_i2c_write(data->client, QN8027_REG_TRANSFER, rate);
}

static void stop_transfer(struct qn8027_i2c_data *data)
{
	qn8027_i2c_write(data->client, QN8027_REG_TRANSFER, 0x00);
}

static UINT8 QNF_SetCh(struct qn8027_i2c_data *data, UINT16 freq)
{
	UINT16 freqval;
	UINT8 regval;

	if (freq < 8700 || freq > 10800) {
		pr_info("%s: the freq is not right\n", __func__);
		return 1;
	}
	freqval = (freq - 8700) / 2;
	regval = qn8027_i2c_read(data->client, QN8027_REG_CHANNEL);
	regval &= ~QN8027_CHANNEL_MASK;
	regval |= ((freqval >> QN8027_CHANNEL_SHIFT) & QN8027_CHANNEL_MASK);
	qn8027_i2c_write(data->client, QN8027_REG_CHANNEL, regval);
	data->freq = freq;
	return 0;
}

static UINT8 QNF_SetMute(struct qn8027_i2c_data *data, int mute)
{
	fm_set_audio_mute(data, mute);
	return 0;
}

static int QNF_GetMute(struct qn8027_i2c_data *data)
{
	return fm_get_audio_mute(data);
}

static void QND_TXSetPower(struct qn8027_i2c_data *data, unsigned char power)
{
	fm_set_txpower(data, power);
}

static int SearchQN8027(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	return 0;
}

/* ---- file ops ---- */
static int qn8027_open(struct inode *inode, struct file *file)
{
	return 0;
}

static long qn8027_ioctl(struct file *file, unsigned int cmd,
			 unsigned long arg)
{
	struct qn8027_i2c_data *data = qn8027_data;
	unsigned char value;
	unsigned short freq;
	int mute;

	if (!data)
		return -ENODEV;

	switch (cmd) {
	case 0x06:	/* get/set volume */
		if (copy_from_user(&value, (void __user *)arg,
				   sizeof(value)))
			return -EFAULT;
		fm_set_volume(data, value);
		break;
	case 0x22c:	/* set frequency */
		if (copy_from_user(&freq, (void __user *)arg, sizeof(freq)))
			return -EFAULT;
		QNF_SetCh(data, freq);
		break;
	case 0x7ff7:	/* get mute */
		mute = fm_get_audio_mute(data);
		if (copy_to_user((void __user *)arg, &mute, sizeof(mute)))
			return -EFAULT;
		break;
	case 0xaeff:	/* set mute */
		if (copy_from_user(&mute, (void __user *)arg, sizeof(mute)))
			return -EFAULT;
		fm_set_audio_mute(data, mute);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

static long qn8027_compat_ioctl(struct file *file, unsigned int cmd,
				unsigned long arg)
{
	return qn8027_ioctl(file, cmd, arg);
}

static int qn8027_release(struct inode *inode, struct file *file)
{
	return 0;
}

static const struct file_operations qn8027_misc_fops = {
	.owner = THIS_MODULE,
	.open = qn8027_open,
	.release = qn8027_release,
	.unlocked_ioctl = qn8027_ioctl,
	.compat_ioctl = qn8027_compat_ioctl,
	.llseek = no_llseek,
};

static struct miscdevice qn8027_misc_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "qn8027",
	.fops = &qn8027_misc_fops,
};

/* ---- sysfs ---- */
static ssize_t setfreq_show(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);

	return sprintf(buf, "%d\n", data->freq);
}

static ssize_t setfreq_store(struct device *dev, struct device_attribute *attr,
			     const char *buf, size_t count)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);
	unsigned short freq;

	if (kstrtou16(buf, 10, &freq))
		return -EINVAL;
	QNF_SetCh(data, freq);
	return count;
}

static ssize_t volume_show(struct device *dev, struct device_attribute *attr,
			   char *buf)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);

	return sprintf(buf, "%d\n", fm_get_volume(data));
}

static ssize_t volume_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);
	unsigned char value;

	if (kstrtou8(buf, 10, &value))
		return -EINVAL;
	fm_set_volume(data, value);
	return count;
}

static ssize_t txpa_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);

	return sprintf(buf, "%d\n", fm_get_txpa(data));
}

static ssize_t txpa_store(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);
	unsigned char value;

	if (kstrtou8(buf, 10, &value))
		return -EINVAL;
	fm_set_txpa(data, value);
	return count;
}

static ssize_t txpower_show(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);

	return sprintf(buf, "%d\n", fm_get_txpower(data));
}

static ssize_t txpower_store(struct device *dev, struct device_attribute *attr,
			     const char *buf, size_t count)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);
	unsigned char value;

	if (kstrtou8(buf, 10, &value))
		return -EINVAL;
	fm_set_txpower(data, value);
	return count;
}

static ssize_t audio_mute_show(struct device *dev, struct device_attribute *attr,
			       char *buf)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);

	return sprintf(buf, "%d\n", fm_get_audio_mute(data));
}

static ssize_t audio_mute_store(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);
	int mute;

	if (kstrtoint(buf, 10, &mute))
		return -EINVAL;
	fm_set_audio_mute(data, mute);
	return count;
}

static ssize_t impendance_show(struct device *dev, struct device_attribute *attr,
			       char *buf)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);

	return sprintf(buf, "%d\n", fm_get_impendance(data));
}

static ssize_t impendance_store(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);
	unsigned char value;

	if (kstrtou8(buf, 10, &value))
		return -EINVAL;
	fm_set_impendance(data, value);
	return count;
}

static DEVICE_ATTR_RW(setfreq);
static DEVICE_ATTR_RW(volume);
static DEVICE_ATTR_RW(txpa);
static DEVICE_ATTR_RW(txpower);
static DEVICE_ATTR_RW(audio_mute);
static DEVICE_ATTR_RW(impendance);

static struct attribute *qn8027_attrs[] = {
	&dev_attr_setfreq.attr,
	&dev_attr_volume.attr,
	&dev_attr_txpa.attr,
	&dev_attr_txpower.attr,
	&dev_attr_audio_mute.attr,
	&dev_attr_impendance.attr,
	NULL,
};

static const struct attribute_group qn8027_attr_group = {
	.attrs = qn8027_attrs,
};

/* ---- PM / ADF ---- */
static int qn8027_pm_suspend(struct device *dev)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);

	data->is_suspend = 1;
	stop_transfer(data);
	return 0;
}

static int qn8027_pm_resume(struct device *dev)
{
	struct qn8027_i2c_data *data = dev_get_drvdata(dev);

	data->is_suspend = 0;
	return 0;
}

static const struct dev_pm_ops qn8027_pm_ops = {
	.suspend = qn8027_pm_suspend,
	.resume = qn8027_pm_resume,
};

static int qn8027_adf_event_handler(struct notifier_block *nb,
				    unsigned long event, void *data)
{
	struct qn8027_i2c_data *qdata =
		container_of(nb, struct qn8027_i2c_data, adf_event);

	if (event == 0)		/* screen off */
		qn8027_suspend(qdata);
	else			/* screen on */
		qn8027_resume(qdata);
	return 0;
}

static int qn8027_suspend(struct qn8027_i2c_data *data)
{
	stop_transfer(data);
	return 0;
}

static int qn8027_resume(struct qn8027_i2c_data *data)
{
	return 0;
}

/* ---- probe ---- */
static int qn8027_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct qn8027_i2c_data *data;
	int ret;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data) {
		pr_err("QN8027: Allocate qn8027 context memory failed!\n");
		return -ENOMEM;
	}
	data->client = client;
	data->dev = &client->dev;
	mutex_init(&data->lock);
	qn8027_data = data;
	i2c_set_clientdata(client, data);

	ret = misc_register(&qn8027_misc_device);
	if (ret) {
		pr_err("QN8027: misc_register error!\n");
		goto err_misc;
	}

	ret = sysfs_create_group(&client->dev.kobj, &qn8027_attr_group);
	if (ret)
		goto err_sysfs;

	/* lsec panel registration for suspend/resume */
	data->adf_event.notifier_call = qn8027_adf_event_handler;
	pr_info("<<QN8027_INFO>>[%s:%d] radio driver installing...\n",
		__func__, __LINE__);

	return 0;

err_sysfs:
	misc_deregister(&qn8027_misc_device);
err_misc:
	kfree(data);
	qn8027_data = NULL;
	return ret;
}

static int qn8027_remove(struct i2c_client *client)
{
	struct qn8027_i2c_data *data = i2c_get_clientdata(client);

	sysfs_remove_group(&client->dev.kobj, &qn8027_attr_group);
	misc_deregister(&qn8027_misc_device);
	kfree(data);
	qn8027_data = NULL;
	return 0;
}

static const struct i2c_device_id qn8027_id[] = {
	{ "qn8027", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, qn8027_id);

static const struct of_device_id qn8027_match_table[] = {
	{ .compatible = "lsec,qn8027", },
	{ }
};
MODULE_DEVICE_TABLE(of, qn8027_match_table);

static struct i2c_driver qn8027_driver = {
	.driver = {
		.name = QN8027_DRV_NAME,
		.of_match_table = qn8027_match_table,
		.pm = &qn8027_pm_ops,
	},
	.id_table = qn8027_id,
	.probe = qn8027_probe,
	.remove = qn8027_remove,
};

static int __init init_qn8027_driver(void)
{
	return i2c_add_driver(&qn8027_driver);
}

static void __exit exit_qn8027_driver(void)
{
	i2c_del_driver(&qn8027_driver);
}

module_init(init_qn8027_driver);
module_exit(exit_qn8027_driver);

MODULE_AUTHOR("wusheng<sheng.wu@ls-ec.com>");
MODULE_DESCRIPTION("QN8027 DRIVER V1.1");
MODULE_LICENSE("GPL");
MODULE_VERSION("v0.0");