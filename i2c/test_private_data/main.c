#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/module.h> 
#include <linux/kernel.h>  
#include <linux/kdev_t.h>  // for macro MAJOR MINOR 
#include <linux/fs.h>      // for function register major , minor
#include <linux/types.h>   // for dev_t type
#include <linux/device.h>   // for dev_t type
#include <linux/cdev.h>

static struct i2c_adapter *i2c_master; 
static struct i2c_client *i2c_lcd; 
static dev_t first;
static struct cdev *c_dev;
static struct class *cl;

 struct my_mpu {
         int xnum;
	 struct i2c_client *client;
         struct mutex lock;
 };


static int my_open(struct inode *i , struct file *f)
{
	struct i2c_client *abc = f->private_data;
	////struct my_mpu	 *mpu = container_of(abc, struct my_mpu, client);

	pr_info("client address : %d\n", abc->addr);
	//printk(KERN_ALERT "Device : my_open() xnum is %d\n",mpu->xnum);
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

static struct i2c_board_info lcd_i2c_info = {
	.type = "lcd_i2c",
	.addr = 0x27,
};

static struct i2c_device_id lcd_i2c_id[] = {
	{"lcd_i2c", 1 },
	{},
};
MODULE_DEVICE_TABLE(i2c, lcd_i2c_id);

static int lcd_i2c_probe(struct i2c_client *i2c_dev, const struct i2c_device_id *i2c_dev_id) {
	struct my_mpu *x;
	struct device *dev = &i2c_dev->dev; 
	pr_info("jump to probe\n");
	
	x = kzalloc(sizeof(struct my_mpu), GFP_KERNEL);
	if ( x == NULL) {
		    dev_info(dev, "failt to alloc x\n");
	            return -ENOMEM;
	}
	i2c_set_clientdata(i2c_dev,&x);
	x->xnum = 12;
	mutex_init(&x->lock);
	dev_info(dev, "probe ok\n");

	return 0;
} 
static int lcd_i2c_remove(struct i2c_client *i2c_dev) {
	pr_info("remove driver\n");
	return 0;
}

static struct i2c_driver lcd_i2c_driver = {
	.driver = {
		.owner = THIS_MODULE,
		.name  = "lcd_i2c_driver",
	},	
	.id_table = lcd_i2c_id,
	.probe    = lcd_i2c_probe,
	.remove   = lcd_i2c_remove,
};

static int __init lcd_i2c_init(void) {
	int ret ;
	
	printk(KERN_EMERG "Device driver file example \n");
	if( alloc_chrdev_region(&first , 0 , 1 , "my_ddfile1") < 0)
	{
		return -1;
	}

	if( ( cl = class_create(THIS_MODULE , "my_char_driver_cls1")) == NULL)
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

	pr_info("init module lcd_i2c\n");
	i2c_master = i2c_get_adapter(2);	
	if(i2c_master == NULL ) {
		pr_err("can't get i2c adapter\n");
		return -1;
	}
	i2c_lcd = i2c_new_device(i2c_master, &lcd_i2c_info); 	
	if( i2c_lcd == NULL) {
		pr_err("can't add device \n");	
		i2c_put_adapter(i2c_master);
		return -1;
	}
	pr_err("add new device successfully\n");	

	ret = i2c_add_driver(&lcd_i2c_driver);
	if( ret < 0) {
		pr_err("can't register driver\n");
		i2c_unregister_device(i2c_lcd);
		i2c_put_adapter(i2c_master);	
		return -1;
	}

	return 0;
}
static void __exit lcd_i2c_exit(void) {
	int ret ;

	pr_info("module is removed\n");		
	i2c_unregister_device(i2c_lcd);
	i2c_put_adapter(i2c_master);	

	device_destroy(cl , first);		
	class_destroy(cl);
	cdev_del(c_dev);
	unregister_chrdev_region(first , 1);
	printk(KERN_EMERG "Goodbye\n");
}

module_init(lcd_i2c_init);
module_exit(lcd_i2c_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("test i2c client");



