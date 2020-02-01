#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/timer.h>

/*
	static method declard
	DEFINE_MUTEX(my_mutex);
*/
/*
	dynamic method
*/
typedef struct __my_device {
	struct mutex my_mutex;
	int data;
	struct timer_list t;
}my_device;

my_device *mdev;

void call_back(struct timer_list *t) {

	mutex_unlock(&mdev->my_mutex);

}
static int __init my_module_init(void) {
	
	mdev = kzalloc(sizeof(my_device), GFP_KERNEL);
	if ( !mdev )  {
		pr_err("calloc error");		
		return -ENOMEM;
	}
	mutex_init(&(mdev->my_mutex));
	mdev->data = 1997;
	timer_setup(&mdev->t, call_back, 0);

	mutex_lock(&mdev->my_mutex);

	//timer unclock
	mod_timer(&mdev->t, jiffies + msecs_to_jiffies(10000));

	mutex_lock(&mdev->my_mutex);
	pr_info("%s run successfully\n", __FUNCTION__);
	
	return 0;
}

static void __exit my_module_exit(void) {
	pr_info("%s run successfully\n", __FUNCTION__);
	mutex_unlock(&mdev->my_mutex);
	kfree(mdev);
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("longvh");
MODULE_DESCRIPTION("init module after 10s using mutex");
