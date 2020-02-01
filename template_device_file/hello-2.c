#include <linux/init.h>
#include <linux/module.h> 
#include <linux/kernel.h>  
#include <linux/kdev_t.h>  // for macro MAJOR MINOR 
#include <linux/fs.h>      // for function register major , minor
#include <linux/types.h>   // for dev_t type
#include <linux/device.h>   // for dev_t type
#include <linux/cdev.h>

#define DRIVER_AUTHOR "vu hai long"
#define DRIVER_DSC "device driver file example"

static dev_t first;
static struct cdev *c_dev;
static struct class *cl;


static int my_open(struct inode *i , struct file *f)
{
	printk(KERN_ALERT "Device : my_open()\n");
return 0;
}
static ssize_t my_read(struct file  *f , char __user *buf ,size_t len ,  loff_t *off )
{
	printk(KERN_ALERT "Device : my_read()\n");
	return 0;
}

static ssize_t my_write(struct file  *f , const char __user *buf ,size_t len ,  loff_t *off )
{
	printk(KERN_ALERT "Device : my_write()\n");
	return len;
}
static int my_close(struct inode *i , struct file *f)
{
	printk(KERN_ALERT "Device : my_close()\n");
	return 0;
}

static struct file_operations fops = 
{
		.owner = THIS_MODULE,
		.read  = my_read,
		.write  = my_write,
		.open  = my_open,
		.release  = my_close
};

static int __init hello_init(void)
{
	printk(KERN_EMERG "Device driver file example \n");
	if( alloc_chrdev_region(&first , 0 , 1 , "my_ddfile") < 0)
	{
		return -1;
	}

	if( ( cl = class_create(THIS_MODULE , "my_char_driver_cls")) == NULL)
	{
		unregister_chrdev_region(first , 1);
		return -1;
	}
 	if( device_create(cl , NULL , MKDEV(MAJOR(first)  , MINOR(first)) , NULL , "my_chd_file%d", 0) == NULL)
	{
			class_destroy(cl);
			unregister_chrdev_region(first , 1);
			return -1;
	}
	c_dev = cdev_alloc();
	cdev_init(c_dev ,&fops); 
	if( (cdev_add(c_dev , first , 1))  == -1)
	{
		device_destroy(cl , first);		
		class_destroy(cl);
		unregister_chrdev_region(first , 1);
		return -1;
	}

	printk(KERN_EMERG "<major , minor > : <%d ,%d>\n",MAJOR(first) , MINOR(first));

	return 0;
}

static void __exit hello_exit(void)
{
	device_destroy(cl , first);		
	class_destroy(cl);
	cdev_del(c_dev);
	unregister_chrdev_region(first , 1);
	printk(KERN_EMERG "Goodbye\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DSC);
