#include <linux/delay.h>
#include <linux/module.h>

static int __init my_module_init(void) {

	pr_info("init successfully\n");
	ndelay(10);
	udelay(10);
	mdelay(10);


	msleep(10);
	usleep_range(10,20);
	return 0;
}
static void __exit my_module_exit(void) {
	
	pr_info("exit ok");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Longvh");
MODULE_DESCRIPTION("test delay and sleep in the kernel");
