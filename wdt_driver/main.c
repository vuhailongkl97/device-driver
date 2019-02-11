#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>// for macro MAJOR MINOR
#include <linux/fs.h>// for function register major , minor

#include <linux/miscdevice.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/uaccess.h>


#include <linux/watchdog.h>

#include "ports.h"

#define DRIVER_AUTHOR "vu hai long"
#define DRIVER_DSC "device driver file example"

#define WDT_START 0x44E35000
#define WDT_STOP  0x44E35FFF

#define PRM_WKUP_START 0x44E00D00
#define PRM_WKUP_STOP  0x44E00DFF

#define CM_WKUP_START  0x44E00400
#define CM_WKUP_STOP   0x44E004FF

//30002h
#define CM_WKUP_WDT1_CLKCTRL 0xD4
//8h
#define PM_WKUP_PWRSTCTRL 0x4

#define WATCHDOG_REV		(0x00)
#define WATCHDOG_SYS_CONFIG	(0x10)
#define WATCHDOG_STATUS		(0x14)
#define WATCHDOG_CNTRL		(0x24)
#define WATCHDOG_CRR		(0x28)
#define WATCHDOG_LDR		(0x2c)
#define WATCHDOG_TGR		(0x30)
#define WATCHDOG_WPS		(0x34)
#define WATCHDOG_SPR		(0x48)

#define PTV			1	/* prescale */
#define GET_WLDR_VAL(secs)	(0xffffffff - ((secs) * (32768/(1<<PTV))) + 1)


void __iomem *io;
static dev_t first;
static struct cdev *c_dev;
static struct class *cl;


static void bbb_disable_wdt(void);
static void bbb_set_timeout(int times);
static void bbb_enable_power_wdt(void);
static void bbb_enable_wdt(void);
static void bbb_ping(void);

static int bbb_open(struct inode *i, struct file *f)
{
	pr_alert("Device : my_open()\n");
	bbb_enable_power_wdt();
	pr_emerg("OK ENABLE POWER\n");
	bbb_disable_wdt();
	pr_emerg("OK disable wdt\n");
	io = ioremap(WDT_START, (WDT_STOP - WDT_START));
	//init prescale
	while (ioread32(io + WATCHDOG_WPS) & (1 << 0))
		;
	iowrite32((1 << 5) | (1 << 2), (io + WATCHDOG_CNTRL));
	while (ioread32(io + WATCHDOG_WPS) & (1 << 0))
		;
	pr_emerg("OK init prescale\n");
	// set time out <> Wdt_lrd
	bbb_set_timeout(30);
	// trigger for restart count
	bbb_ping();
	bbb_enable_wdt();
	pr_emerg("OK enable wdt\n");
	iounmap(io);
	return 0;
}
static ssize_t bbb_read(struct file  *f, char __user *buf,
	size_t len, loff_t *off)
{
	pr_alert("Device : my_read()\n");
	return 0;
}

static ssize_t bbb_write(struct file  *f, const char __user *buf,
	size_t len, loff_t *off)
{
	pr_alert("Device : my_write()\n");
	bbb_ping();
	return len;
}
static int bbb_close(struct inode *i, struct file *f)
{
	pr_alert("Device : my_close()\n");
	return 0;
}

static long bbb_ioctl(struct file *file,
	unsigned int cmd, unsigned long arg)
{
	int new_margin;
	void __user *argp = (void __user *)arg;
	int __user *p = argp;

	static const struct watchdog_info ident = {
		.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT
							| WDIOF_MAGICCLOSE,
		.firmware_version = 1,
		.identity = "BBB WDT",
	};

	switch (cmd) {
	case WDIOC_GETSUPPORT:
		if (copy_to_user(argp, &ident, sizeof(ident)))
			return -EFAULT;
		break;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		return put_user(0, p);

	case WDIOC_SETOPTIONS:
	{
		int options, retval = -EINVAL;

		if (get_user(options, p))
			return -EFAULT;

		if (options & WDIOS_DISABLECARD) {
			bbb_disable_wdt();
			retval = 0;
		}
		if (options & WDIOS_ENABLECARD) {
			bbb_ping();
			retval = 0;
		}
		return retval;
	}
	case WDIOC_KEEPALIVE:
		bbb_ping();
		break;

	case WDIOC_SETTIMEOUT:
		if (get_user(new_margin, p))
			return  -EFAULT;
		pr_info("bbb set timeout : %d", new_margin);
		bbb_ping();
		break;
		/* Fall */
	case WDIOC_GETTIMEOUT:
		return put_user(69, p);
	default:
		return -ENOTTY;
	}
	return 0;
}

static void bbb_disable_wdt(void)
{
	unsigned int temp = 0;

	io = ioremap(WDT_START, (WDT_STOP - WDT_START));
	iowrite32(0xAAAA, (io + WATCHDOG_SPR));
	do {
		temp = readl_relaxed(io + WATCHDOG_WPS) & (1 << 4);
	} while (temp);
	iowrite32(0x5555, (io + WATCHDOG_SPR));
	do {
		temp = readl_relaxed(io + WATCHDOG_WPS) & (1 << 4);
	} while (temp);
}
static void bbb_enable_wdt(void)
{
	unsigned int temp = 0;

	io = ioremap(WDT_START, (WDT_STOP - WDT_START));
	iowrite32(0xBBBB, (io + WATCHDOG_SPR));
	do {
		temp = ioread32(io + WATCHDOG_WPS) & (1 << 4);
	} while (temp);
	iowrite32(0x4444, (io + WATCHDOG_SPR));
	do {
		temp = ioread32(io + WATCHDOG_WPS) & (1 << 4);
	} while (temp);
}
static void bbb_enable_power_wdt(void)
{
	unsigned long temp = 0;

	pr_emerg("Driver WTD\n");
	io = ioremap(PRM_WKUP_START, (PRM_WKUP_STOP - PRM_WKUP_START));
	temp = ioread32(io + PM_WKUP_PWRSTCTRL);
	temp = ioread32(io + PM_WKUP_PWRSTCTRL);

	io = ioremap(CM_WKUP_START, (CM_WKUP_STOP - CM_WKUP_START));
	temp = ioread32(io + CM_WKUP_WDT1_CLKCTRL);
	temp |= 0x02;

	iowrite32(temp, (io + CM_WKUP_WDT1_CLKCTRL));
	temp = ioread32(io + CM_WKUP_WDT1_CLKCTRL);


}
static void bbb_ping(void)
{
	unsigned int temp = 0;

	temp = ioread32(io + WATCHDOG_TGR);
	while (ioread32(io + WATCHDOG_WPS) & (1 << 3))
		;
	iowrite32(~temp, (io + WATCHDOG_TGR));
	while (ioread32(io + WATCHDOG_WPS) & (1 << 3))
		;
	pr_emerg("OK trigger\n");

}
static void bbb_set_timeout(int times)
{
	while (ioread32(io + WATCHDOG_WPS) & (1 << 2))
		;

	iowrite32(GET_WLDR_VAL(times), (io + WATCHDOG_LDR))
		;

	while (ioread32(io + WATCHDOG_WPS) & (1 << 2))
		;

	pr_emerg("OK set timeout\n");
}
static const struct file_operations fops = {
	.owner		= THIS_MODULE,
	.write		= bbb_write,
	.unlocked_ioctl	= bbb_ioctl,
	.open		= bbb_open,
	.read		= bbb_read,
	.release	= bbb_close,

};
static int __init hello_init(void)
{
	if (alloc_chrdev_region(&first, 0, 1, "my_ddfile") < 0)
		return -1;

	cl = class_create(THIS_MODULE, "my_char_driver_cls");

	if (cl == NULL) {
		unregister_chrdev_region(first, 1);
		return -1;
	}
	if (device_create(cl, NULL, MKDEV(MAJOR(first),
		MINOR(first)), NULL, "my_watchdog") == NULL) {
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	c_dev = cdev_alloc();
	cdev_init(c_dev, &fops);
	if ((cdev_add(c_dev, first, 1)) == -1) {
		device_destroy(cl, first);
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	return 0;
}

static void __exit hello_exit(void)
{
	device_destroy(cl, first);
	class_destroy(cl);
	cdev_del(c_dev);
	unregister_chrdev_region(first, 1);
	bbb_disable_wdt();
	pr_info("Goodbye\n");
}
module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DSC);

