#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/i2c.h>

static struct i2c_adapter *i2c_master; 
static struct i2c_client *i2c_lcd; 

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
	int ret;
	char buf  = 0xFF;
	pr_info("jump to probe\n");
	
	ret = i2c_master_send(i2c_dev, &buf, 1);
	if ( ret < 0 ) {
		pr_err("can't send to slave\n");
		return -1;
	}
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
	char buf = 0;
	int ret ;
	pr_info("module is removed\n");		
	ret = i2c_master_send(i2c_lcd, &buf, 1);
	if ( ret <0) {
		pr_info("can't send on module exit\n");	
	}
	i2c_unregister_device(i2c_lcd);
	i2c_put_adapter(i2c_master);	
}

module_init(lcd_i2c_init);
module_exit(lcd_i2c_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("test i2c client");

