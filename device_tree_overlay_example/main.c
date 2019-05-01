#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/io.h>

struct my_device {
	int secret_number ;
	struct device *mdev;
	struct file_operations fops;
	struct mutex lock;
};
static int my_probe(struct platform_device *pdev) {
	//	struct resource  *res;
	//	void __iomem *base;
	struct my_device *mdevice;	
	struct device *dev = &pdev->dev;

	pr_info("jump to probe\n");
	mdevice = kzalloc(sizeof(struct my_device), GFP_KERNEL);
	
	if( mdevice == NULL) {
		dev_info(dev, "fail to alloc mdevice\n");
		return -ENOMEM;
	}
	dev_info(dev, "alloc ok");
	mdevice->mdev = dev;
	mdevice->secret_number = 1997;
	mutex_init(&mdevice->lock);
	platform_set_drvdata(pdev, mdevice);
	
	return 0;

}
static int my_remove(struct platform_device *pdev) {
	struct my_device *my_dev ;
	//my_dev = container_of(pdev->dev, struct my_device , mdev);
	my_dev = platform_get_drvdata(pdev);
	pr_info("secret number get from containter of is : %d\n", my_dev->secret_number);
	
	kfree(my_dev);
	return 0;
}
static const struct of_device_id test_id[] = {
	{ .compatible ="hehe,longvh",  },
	{},
};
MODULE_DEVICE_TABLE(of, test_id);

static struct platform_driver test_driver = {
	.probe = my_probe,	
	.remove = my_remove,
	.driver = {
		.name = "test driver",
		.of_match_table = test_id,
	},
};

module_platform_driver(test_driver);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Longvh");
