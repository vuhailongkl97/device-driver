#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/ioctl.h>
#include <linux/poll.h>
#include <linux/uaccess.h>

static DECLARE_WAIT_QUEUE_HEAD(my_wq); 
static DECLARE_WAIT_QUEUE_HEAD(my_rq); 


static int my_misc_open(struct inode *ino, struct file *fp) {

	pr_info("misc open\n");
	return 0;
}
static int my_misc_close(struct inode *ino, struct file *fp) {

	return 0;
}
static unsigned int my_poll(struct file *file, poll_table *wait) 
{ 
   	 unsigned int reval_mask = 0; 

	 pr_info("go to my poll\n");
	 poll_wait(file, &my_wq, wait); 
	 poll_wait(file, &my_rq, wait); 
     if (false) 
	    reval_mask |= (POLLIN | POLLRDNORM); 
	 if (false) 
	    reval_mask |= (POLLOUT | POLLWRNORM); 
	//wake_up_interruptible(&my_rq); 
	//wake_up_interruptible(&my_wq); 
	pr_info("test to run this command\n");
     return reval_mask; 
} 

static struct file_operations my_misc_fops = {
	.owner = THIS_MODULE ,
	.open  = my_misc_open,
	.release  = my_misc_close,
	.poll  = my_poll
};

static struct miscdevice my_misc_device = {
	.minor = MISC_DYNAMIC_MINOR,	
	.name  = "my_misc_poll",
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

