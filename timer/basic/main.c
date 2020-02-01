#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>


static struct timer_list t;

void call_back(struct timer_list *t) {
	pr_info("called %s , hz : %d, jiffies :%ld \n", __FUNCTION__, HZ, jiffies);	

	/* 
		need update exprire time if you want to 
		looping call_back
	*/
}

static int __init my_module_init(void) {

	pr_info("my module init\n");

	timer_setup(&t, call_back, 0);
	mod_timer(&t, jiffies + msecs_to_jiffies(10000));

	return 0;
}
static void __exit my_module_exit(void) {
	int ret;

	ret = del_timer(&t);

	if(ret)
		pr_err("timer is in use\n");	

	pr_info("remove successfully\n");
}
module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LONGVH");
MODULE_DESCRIPTION("EXAMPLE TIMER MODULE");
