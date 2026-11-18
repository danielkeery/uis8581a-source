// SPDX-License-Identifier: GPL-2.0
/*
 * CH7026 CVBS/HDMI encoder driver
 * Author: wusheng <sheng.wu@ls-ec.com>   License: GPL   version v0.0
 *
 * Reconstructed from DWARF debug info + ARM64 disassembly of the shipped
 * out-of-tree module:
 *   /work/users/sharebsp/workdir/used8581/bsp/modules/radio/ch7026/ch7026.c
 *
 * Facts recovered:
 *   - single source file ch7026.c (~880 lines)
 *   - i2c child on i2c4 @ 0x76, compatible "lsec,ch7026"
 *   - struct ch7026_position_parm { vposition, hposition, vsync, hsync }
 *   - CVBS video out control: switch, reset-dft, reset-position,
 *     hpos/vpos/hsync/vsync read/write, parama confirm
 *   - ioctl cmds: 0x3ff7, 0x8fe, 0xd; misc device + lsec panel notifier
 *   - depends on lsec framework (gp_lsecinfo, isPanelcfgOK, lsec_panel_*)
 *
 * Best-effort functional reconstruction; verify against .ko before deploy.
 * (Device has NO HDMI/CVBS output wiring; module present but unused on this board.)
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/uaccess.h>

#define CH7026_DRV_NAME	"ch7026"

/* ---- CH7026 registers ---- */
#define CH7026_REG_VIDEO_CTRL	0x00
#define CH7026_REG_VPOS	0x30
#define CH7026_REG_HPOS	0x31
#define CH7026_REG_VSYNC	0x32
#define CH7026_REG_HSYNC	0x33
#define CH7026_REG_PARA	0x34
#define CH7026_REG_RESET	0x3f

struct ch7026_position_parm {
	unsigned short vposition;
	unsigned short hposition;
	unsigned short vsync;
	unsigned short hsync;
};

struct ch7026_i2c_data {
	struct i2c_client *client;
	struct device *dev;
	struct mutex lock;
	struct ch7026_position_parm pos;
	int is_suspend;
	struct notifier_block adf_event;
};

static struct ch7026_i2c_data *ch7026_data;
static int ch7026_resume(void);

/* ---- low-level i2c ---- */
static int ch7026_readreg(void *arg)
{
	struct ch7026_i2c_data *data = ch7026_data;
	u8 *reg = (u8 *)arg;

	return i2c_smbus_read_byte_data(data->client, reg[0]);
}

static int ch7026_writereg(void *arg)
{
	struct ch7026_i2c_data *data = ch7026_data;
	u8 *reg = (u8 *)arg;

	return i2c_smbus_write_byte_data(data->client, reg[0], reg[1]);
}

/* ---- position read/write ---- */
int ch7026_hpos_read(void *arg)
{
	struct ch7026_i2c_data *data = ch7026_data;

	pr_info("<<CH7026_INFO>>[%s:%d] ch7026 hposition:%d\n",
		__func__, __LINE__, data->pos.hposition);
	return data->pos.hposition;
}

int ch7026_hpos_write(void *arg)
{
	struct ch7026_i2c_data *data = ch7026_data;
	unsigned short *val = (unsigned short *)arg;

	data->pos.hposition = *val;
	pr_info("<<CH7026_INFO>>[%s:%d] ch7026 hposition write:%d\n",
		__func__, __LINE__, *val);
	return 0;
}

int ch7026_vpos_read(void *arg)
{
	struct ch7026_i2c_data *data = ch7026_data;

	pr_info("<<CH7026_INFO>>[%s:%d] ch7026 vposition:%d\n",
		__func__, __LINE__, data->pos.vposition);
	return data->pos.vposition;
}

int ch7026_vpos_write(void *arg)
{
	struct ch7026_i2c_data *data = ch7026_data;
	unsigned short *val = (unsigned short *)arg;

	data->pos.vposition = *val;
	pr_info("<<CH7026_INFO>>[%s:%d] ch7026 vposition write:%d\n",
		__func__, __LINE__, *val);
	return 0;
}

int ch7026_hsync_read(void *arg)
{
	struct ch7026_i2c_data *data = ch7026_data;

	pr_info("<<CH7026_INFO>>[%s:%d] ch7026 hsync:%d\n",
		__func__, __LINE__, data->pos.hsync);
	return data->pos.hsync;
}

int ch7026_hsync_write(void *arg)
{
	struct ch7026_i2c_data *data = ch7026_data;
	unsigned short *val = (unsigned short *)arg;

	data->pos.hsync = *val;
	pr_info("<<CH7026_INFO>>[%s:%d] ch7026 hsync write:%d\n",
		__func__, __LINE__, *val);
	return 0;
}

int ch7026_vsync_read(void *arg)
{
	struct ch7026_i2c_data *data = ch7026_data;

	pr_info("<<CH7026_INFO>>[%s:%d] ch7026 vsync:%d\n",
		__func__, __LINE__, data->pos.vsync);
	return data->pos.vsync;
}

int ch7026_vsync_write(void *arg)
{
	struct ch7026_i2c_data *data = ch7026_data;
	unsigned short *val = (unsigned short *)arg;

	data->pos.vsync = *val;
	pr_info("<<CH7026_INFO>>[%s:%d] ch7026 vsync write:%d\n",
		__func__, __LINE__, *val);
	return 0;
}

/* ---- parama confirm / CVBS switch ---- */
int ch7026_parama_confirm(void *arg)
{
	pr_info("<<CH7026-DBG>>[%s:%d] ch7026 get parama\n", __func__, __LINE__);
	return 0;
}

int CVBS_Out_Switch(void *arg)
{
	pr_info("<<CH7026-ERR>>[%s:%d] CH7026 CVBS_drv_Switch! %d\n",
		__func__, __LINE__, 1);
	return 0;
}

int CVBS_Out_ResetDft(void *arg)
{
	pr_info("<<CH7026-ERR>>[%s:%d] CH7026 reset dft\n", __func__, __LINE__);
	return 0;
}

int CVBS_Out_ResetPosition(void *arg)
{
	pr_info("<<CH7026-ERR>>[%s:%d] CH7026 reset position\n",
		__func__, __LINE__);
	return 0;
}

int CVBS_drv_Switch(int on)
{
	pr_info("<<CH7026-ERR>>[%s:%d] CH7026 CVBS_drv_Switch! %d\n",
		__func__, __LINE__, on);
	return 0;
}

/* ---- file ops ---- */
static int ch026_open(struct inode *inode, struct file *file)
{
	return 0;
}

static ssize_t ch026_read_data(struct file *file, char *buf, size_t len,
			       loff_t *off)
{
	return 0;
}

static int ch026_release(struct inode *inode, struct file *file)
{
	return 0;
}

static long ch026_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct ch7026_i2c_data *data = ch7026_data;
	unsigned short value;

	if (!data)
		return -ENODEV;

	switch (cmd) {
	case 0x3ff7:	/* get position */
		if (copy_to_user((void __user *)arg, &data->pos,
				 sizeof(data->pos)))
			return -EFAULT;
		break;
	case 0x8fe:	/* set position */
		if (copy_from_user(&data->pos, (void __user *)arg,
				   sizeof(data->pos)))
			return -EFAULT;
		break;
	case 0xd:	/* CVBS switch */
		CVBS_drv_Switch(1);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

static long ch026_compat_ioctl(struct file *file, unsigned int cmd,
			       unsigned long arg)
{
	return ch026_ioctl(file, cmd, arg);
}

static const struct file_operations ch7026_misc_fops = {
	.owner = THIS_MODULE,
	.open = ch026_open,
	.read = ch026_read_data,
	.release = ch026_release,
	.unlocked_ioctl = ch026_ioctl,
	.compat_ioctl = ch026_compat_ioctl,
	.llseek = no_llseek,
};

static struct miscdevice ch7026_misc_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "ch7026",
	.fops = &ch7026_misc_fops,
};

/* ---- ADF ---- */
static int ch7026_adf_event_handler(struct notifier_block *nb,
				    unsigned long event, void *data)
{
	struct ch7026_i2c_data *cdata =
		container_of(nb, struct ch7026_i2c_data, adf_event);

	if (event == 0)
		ch7026_resume();
	else
		ch7026_resume();
	return 0;
}

static int ch7026_resume(void)
{
	pr_info("<<CH7026_INFO>>[%s:%d] ch7026 resume\n", __func__, __LINE__);
	return 0;
}

/* ---- probe ---- */
static int ch7026_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ch7026_i2c_data *data;
	int ret;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	data->client = client;
	data->dev = &client->dev;
	mutex_init(&data->lock);
	ch7026_data = data;
	i2c_set_clientdata(client, data);

	ret = misc_register(&ch7026_misc_device);
	if (ret) {
		pr_err("<<CH7026-ERR>>[%s:%d] misc_register failed!\n",
			__func__, __LINE__);
		goto err_misc;
	}
	return 0;

err_misc:
	kfree(data);
	ch7026_data = NULL;
	return ret;
}

static int ch7026_remove(struct i2c_client *client)
{
	misc_deregister(&ch7026_misc_device);
	kfree(ch7026_data);
	ch7026_data = NULL;
	return 0;
}

static const struct i2c_device_id ch7026_id[] = {
	{ "ch7026", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, ch7026_id);

static const struct of_device_id ch7026_of_match[] = {
	{ .compatible = "lsec,ch7026", },
	{ }
};
MODULE_DEVICE_TABLE(of, ch7026_of_match);

static struct i2c_driver ch7026_driver = {
	.driver = {
		.name = CH7026_DRV_NAME,
		.of_match_table = ch7026_of_match,
	},
	.id_table = ch7026_id,
	.probe = ch7026_probe,
	.remove = ch7026_remove,
};

static int __init init_ch7026_driver(void)
{
	return i2c_add_driver(&ch7026_driver);
}

static void __exit exit_ch7026_driver(void)
{
	i2c_del_driver(&ch7026_driver);
}

module_init(init_ch7026_driver);
module_exit(exit_ch7026_driver);

MODULE_AUTHOR("wusheng<sheng.wu@ls-ec.com>");
MODULE_DESCRIPTION("CH7026 DRIVER V1.1");
MODULE_LICENSE("GPL");
MODULE_VERSION("v0.0");