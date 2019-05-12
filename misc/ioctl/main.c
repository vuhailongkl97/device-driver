#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/ioctl.h>

static int my_misc_open(struct inode *ino, struct file *fp) {

	pr_info("misc open\n");
	return 0;
}
static int my_misc_close(struct inode *ino, struct file *fp) {

	return 0;
}
static ssize_t my_misc_write(struct file *fp, const char *buf, size_t len, loff_t *pos) {

	pr_info("my misc write\n");
	return len;
}

static ssize_t my_misc_read(struct file *fp, char *buf, size_t len, loff_t *pos) {

	pr_info("my misc read\n");
	

	return 0;
}

static long my_misc_ioctl(struct file *fp, unsigned int cmd, unsigned long args) {
	pr_info("my misc ioctl\n");


	switch(cmd) {
		case SET_BAUBRATE:
			pr_info("setup baudrate\n");
			break;
		case GET_INFO_DEV:
			pr_info("get information device\n");
			break;
		default:
			pr_error("incorrect command via ioctl method\n");
			return -ENOTTY;
	}

	return 0;
}
static struct file_operations my_misc_fops = {
	.owner = THIS_MODULE ,
	.open  = my_misc_open,
	.release  = my_misc_close,
	.write = my_misc_write,
	.read  = my_misc_read,
	.unlocked_ioctl = my_misc_ioctl
};

static struct miscdevice my_misc_device = {
	.minor = MISC_DYNAMIC_MINOR,	
	.name  = "my_misc",
	.fops  = &my_misc_fops
};

static int __init my_module_init(void) {

	pr_info("init ok\n");
	return misc_register(&my_misc_device);
}

static void __exit my_module_exit(void) {
	pr_info("exit ok");

	misc_deregister(&my_misc_device);
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LONGVH");
MODULE_DESCRIPTION("MISC EXAMPLE");

