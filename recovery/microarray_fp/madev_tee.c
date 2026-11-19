// SPDX-License-Identifier: GPL-2.0
/*
 * Microarray AFS121 fingerprint sensor driver (TEE-based)
 * Author: Microarray   License: GPL
 *
 * Reconstructed from DWARF debug info + ARM64 disassembly of the shipped
 * out-of-tree module:
 *   /work/users/sharebsp/workdir/used8581/bsp/modules/input/fingerprint/microarray/
 *     madev_tee.c
 *     x86-settings.c
 *
 * Facts recovered:
 *   - platform driver, of compatible "microarray,afs121"
 *   - SPI transport (ma_spi_t), char device "madev0" (major dynamic, minor 0)
 *   - input device (fingerprint), fb notifier for panel suspend/resume
 *   - gpios from DT: "fpint-gpios" (int_gpio), en_gpio
 *   - ioctl cmds magic 0x4d: 0x4d20/0x4d21/0x4d26/0x4d29/0x4d2a/0x4d35/0x4d36
 *   - mmap support (mas_mmap) for TEE buffer sharing
 *   - wakelock (microarray_process_wakelock), threaded irq
 *
 * Best-effort functional reconstruction; verify against .ko before deploy.
 * NOTE: device has NO fingerprint sensor; module shipped but unused on this board.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/spi/spi.h>
#include <linux/input.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/pm_wakeup.h>
#include <linux/fb.h>
#include <linux/workqueue.h>

#define MAFP_NAME		"madev"
#define MAFP_CLASS		"madev"
#define MAFP_DEVNODE		"madev0"

#define MAFP_IOC_MAGIC		0x4d

/* ioctl commands (recovered) */
#define MAFP_IOC_GET_INFO	_IO(MAFP_IOC_MAGIC, 0x00)	/* 0x4d20 */
#define MAFP_IOC_SET_POWER	_IO(MAFP_IOC_MAGIC, 0x01)	/* 0x4d21 */
#define MAFP_IOC_GET_STATUS	_IO(MAFP_IOC_MAGIC, 0x06)	/* 0x4d26 */
#define MAFP_IOC_ENABLE		_IO(MAFP_IOC_MAGIC, 0x09)	/* 0x4d29 */
#define MAFP_IOC_DISABLE	_IO(MAFP_IOC_MAGIC, 0x0a)	/* 0x4d2a */
#define MAFP_IOC_GET_POWER	_IO(MAFP_IOC_MAGIC, 0x15)	/* 0x4d35 */
#define MAFP_IOC_WAKEUP		_IO(MAFP_IOC_MAGIC, 0x16)	/* 0x4d36 */

struct fprint_dev {
	dev_t idd;
	int major;
	int minor;
	struct cdev *chd;
	struct class *cls;
	struct device *dev;
};

/* project globals (recovered) */
static struct spi_device *ma_spi_t;
static struct input_dev *ma_input_t;
static struct fprint_dev *sdev;
static struct notifier_block notifier;
static unsigned int int_gpio = -1;
static int en_gpio = -1;

static struct wakeup_source *ma_wake_lock;

static void mas_work(struct work_struct *work);
static DECLARE_WORK(ma_work, mas_work);

static int mas_get_platform(void);
static int mas_remove_platform(void);

/* ---- SPI select/enable ---- */
static void mas_select_transfer(struct spi_device *spi, int enable)
{
	/* SPI chip-select via en_gpio */
	if (en_gpio >= 0)
		gpio_set_value(en_gpio, enable ? 0 : 1);
}

static void ma_spi_change(struct spi_device *spi, unsigned int mode, int bit)
{
	spi->mode = mode;
	spi->bits_per_word = bit;
	spi_setup(spi);
}

void mas_enable_spi_clock(struct spi_device *spi)
{
	/* enable SPI / periph clock (usually a no-op, kernel manages) */
}

void mas_disable_spi_clock(struct spi_device *spi)
{
}

/* ---- gpio ---- */
int mas_finger_set_spi(int enable)
{
	mas_select_transfer(ma_spi_t, enable);
	return 0;
}

int mas_finger_set_power(int on)
{
	/* power GPIO: en_gpio */
	if (en_gpio >= 0)
		gpio_set_value(en_gpio, on);
	return 0;
}

int mas_finger_set_gpio_info(int on)
{
	mas_finger_set_power(on);
	mas_finger_set_spi(on);
	return 0;
}

int mas_finger_set_eint(int enable)
{
	if (enable)
		enable_irq(int_gpio);
	else
		disable_irq_nosync(int_gpio);
	return 0;
}

int mas_finger_get_gpio_info(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	int gpio;

	/* reset / power gpio */
	gpio = of_get_named_gpio(np, "microarray_eint", 0);
	if (gpio_is_valid(gpio)) {
		if (gpio_request(gpio, "microarray_eint"))
			pr_err("gpio request error!\n");
		int_gpio = gpio;
	}
	/* interrupt gpio */
	gpio = of_get_named_gpio(np, "fpint-gpios", 0);
	if (gpio_is_valid(gpio)) {
		if (gpio_request(gpio, "fpint-gpios"))
			pr_err("gpio request error!\n");
		en_gpio = gpio;
	}
	pr_info("MAFP_%s: mas_get_irq = %d\n", __func__, int_gpio);
	return 0;
}

int mas_set_enable_gpio(struct platform_device *pdev)
{
	return mas_finger_get_gpio_info(pdev);
}

unsigned int mas_get_irq(struct platform_device *pdev)
{
	int irq;

	irq = gpio_to_irq(int_gpio);
	if (irq < 0) {
		pr_err("gpio_to_irq failed\n");
		return irq;
	}
	pr_info("MAFP_%s: mas_get_irq = %d\n", __func__, irq);
	return irq;
}

int mas_get_interrupt_gpio(unsigned int irq)
{
	return int_gpio;
}

int mas_switch_power(unsigned int on)
{
	mas_finger_set_power(on);
	return 0;
}

/* ---- IRQ / work ---- */
static irqreturn_t mas_interrupt(int irq, void *dev_id)
{
	pr_info("7microarray fingerprint interrupt happened!\n");
	queue_work(system_wq, &ma_work);
	return IRQ_HANDLED;
}

static void mas_work(struct work_struct *work)
{
	/* wake user-space via input event */
	if (ma_input_t) {
		input_event(ma_input_t, EV_KEY, 0x100, 1);
		input_sync(ma_input_t);
	}
	pm_wakeup_ws_event(ma_wake_lock, 100, true);
}

/* ---- mmap (TEE buffer) ---- */
static int mas_mmap(struct file *file, struct vm_area_struct *vma)
{
	return 0;
}

/* ---- ioctl ---- */
static long mas_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int value = 0;

	switch (cmd) {
	case MAFP_IOC_SET_POWER:
		if (copy_from_user(&value, (void __user *)arg, sizeof(value)))
			return -EFAULT;
		mas_finger_set_power(value);
		break;
	case MAFP_IOC_GET_INFO:
	case MAFP_IOC_GET_STATUS:
	case MAFP_IOC_ENABLE:
	case MAFP_IOC_DISABLE:
	case MAFP_IOC_GET_POWER:
	case MAFP_IOC_WAKEUP:
		if (copy_to_user((void __user *)arg, &value, sizeof(value)))
			return -EFAULT;
		break;
	default:
		pr_info("mas_ioctl no such cmd\n");
		return -EINVAL;
	}
	return 0;
}

static long mas_compat_ioctl(struct file *file, unsigned int cmd,
			     unsigned long arg)
{
	return mas_ioctl(file, cmd, arg);
}

/* ---- file ops ---- */
static const struct file_operations sfops = {
	.owner = THIS_MODULE,
	.mmap = mas_mmap,
	.unlocked_ioctl = mas_ioctl,
	.compat_ioctl = mas_compat_ioctl,
};

/* ---- fb notifier (suspend/resume) ---- */
static int mas_fb_notifier_callback(struct notifier_block *nb,
				    unsigned long event, void *data)
{
	struct fb_event *ev = data;
	int blank = *(int *)ev->data;

	if (event == FB_EVENT_BLANK && blank == FB_BLANK_UNBLANK)
		mas_finger_set_gpio_info(1);
	else if (event == FB_EVENT_BLANK && blank == FB_BLANK_POWERDOWN)
		mas_finger_set_gpio_info(0);
	return 0;
}

/* ---- platform driver ---- */
static int mas_plat_probe(struct platform_device *pdev)
{
	int ret;

	pr_info("mas_plat_probe do mas_finger_get_gpio_info\n");
	ret = mas_finger_get_gpio_info(pdev);
	if (ret)
		return ret;
	pr_info("mas_plat_probe do mas_finger_set_gpio_info\n");
	mas_finger_set_gpio_info(1);
	return 0;
}

static int mas_plat_remove(struct platform_device *pdev)
{
	return mas_remove_platform();
}

static const struct of_device_id sof_match[] = {
	{ .compatible = "microarray,afs121", },
	{ }
};
MODULE_DEVICE_TABLE(of, sof_match);

static struct platform_driver spdrv = {
	.probe = mas_plat_probe,
	.remove = mas_plat_remove,
	.driver = {
		.name = "madev",
		.of_match_table = sof_match,
	},
};

/* ---- module init/exit ---- */
static int mas_get_platform(void)
{
	return platform_driver_register(&spdrv);
}

static int mas_remove_platform(void)
{
	platform_driver_unregister(&spdrv);
	return 0;
}

static int __init mas_init(void)
{
	int ret;

	/* char device */
	sdev = kzalloc(sizeof(*sdev), GFP_KERNEL);
	if (!sdev)
		return -ENOMEM;

	ret = alloc_chrdev_region(&sdev->idd, 0, 1, MAFP_NAME);
	if (ret) {
		pr_err("alloc_chrdev_region error!\n");
		goto err_region;
	}
	sdev->major = MAJOR(sdev->idd);
	sdev->minor = MINOR(sdev->idd);

	sdev->chd = cdev_alloc();
	if (!sdev->chd) {
		pr_err("cdev_alloc error!\n");
		goto err_cdev;
	}
	cdev_init(sdev->chd, &sfops);
	sdev->chd->owner = THIS_MODULE;
	ret = cdev_add(sdev->chd, sdev->idd, 1);
	if (ret)
		goto err_cdev;

	sdev->cls = class_create(THIS_MODULE, MAFP_CLASS);
	if (IS_ERR(sdev->cls))
		goto err_class;
	sdev->dev = device_create(sdev->cls, NULL, sdev->idd, NULL, MAFP_DEVNODE);
	if (IS_ERR(sdev->dev))
		goto err_dev;

	/* input device */
	ma_input_t = input_allocate_device();
	if (!ma_input_t) {
		pr_err("input_allocate_device failed.\n");
		goto err_input;
	}
	ma_input_t->name = "madev";
	set_bit(EV_KEY, ma_input_t->evbit);
	ret = input_register_device(ma_input_t);
	if (ret) {
		pr_err("failed to register input device.\n");
		goto err_input;
	}

	/* irq */
	{
		unsigned int irq = mas_get_irq(NULL);
		ret = request_threaded_irq(irq, NULL, mas_interrupt,
					   IRQF_TRIGGER_FALLING, "madev", NULL);
		if (ret) {
			pr_err("request irq\n");
			goto err_irq;
		}
	}

	/* wake lock */
	ma_wake_lock = wakeup_source_register("madev");
	INIT_WORK(&ma_work, mas_work);

	/* panel notifier */
	notifier.notifier_call = mas_fb_notifier_callback;
	fb_register_client(&notifier);

	ret = mas_get_platform();
	if (ret)
		pr_info("MAFP mas_get_platform spi_register_driver ret = %d\n", ret);

	pr_info("MAFP_%s: probe complete\n", __func__);
	return 0;

err_irq:
	input_unregister_device(ma_input_t);
err_input:
	device_destroy(sdev->cls, sdev->idd);
err_dev:
	class_destroy(sdev->cls);
err_class:
	cdev_del(sdev->chd);
err_cdev:
	unregister_chrdev_region(sdev->idd, 1);
err_region:
	kfree(sdev);
	return ret;
}

static void __exit mas_exit(void)
{
	fb_unregister_client(&notifier);
	wakeup_source_unregister(ma_wake_lock);
	input_unregister_device(ma_input_t);
	device_destroy(sdev->cls, sdev->idd);
	class_destroy(sdev->cls);
	cdev_del(sdev->chd);
	unregister_chrdev_region(sdev->idd, 1);
	kfree(sdev);
	platform_driver_unregister(&spdrv);
}

module_init(mas_init);
module_exit(mas_exit);

MODULE_AUTHOR("Microarray");
MODULE_DESCRIPTION("Driver for microarray fingerprint sensor");
MODULE_LICENSE("GPL");