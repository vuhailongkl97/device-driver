#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/ioctl.h>
#include <linux/moduleparam.h>

int my_int = 97;
char *my_name = "longvh";
module_param(my_int, int, S_IRUGO);
module_param(my_name, charp, S_IRUGO);

MODULE_PARM_DESC(my_int, "interger number as argument passing");
MODULE_PARM_DESC(my_name, "name as argument passing");

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

	pr_info("init ok. hello %s\n",my_name);
	pr_info("my int is %d\n", my_int);
	misc_register(&my_misc_device);
	return 0;
}

static void __exit my_module_exit(void) {
	pr_info("exit ok");

	misc_deregister(&my_misc_device);
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LONGVH");
MODULE_DESCRIPTION("MISC MODULE PARAM");

