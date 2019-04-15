#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/io.h>

static int my_probe(struct platform_device *pdev) {
	struct resource  *res;
	void __iomem *base;
	pr_info("jump to probe\n");
	
	res =  platform_get_resource(pdev, IORESOURCE_MEM ,0);
	base = devm_ioremap_resource(&pdev->dev, res); 
	if (IS_ERR(base)) 
    		return PTR_ERR(base); 

	int irq = platform_get_irq(pdev, 0); 
	pr_alert("base address of spi is : %ld\n", res->start);
	pr_alert("irq of spi is : %ld\n", irq);
	return 0;

}
static const struct of_device_id test_id[] = {
	{ .compatible ="hehe,longvh12",  },
	{},
};
MODULE_DEVICE_TABLE(of, test_id);

static struct platform_driver test_driver = {
	.probe = my_probe,	
	.driver = {
		.name = "test driver",
		.of_match_table = test_id,
	},
};

static int __init my_init(void) {
	struct device_node *temp;
	pr_info("module init\n");

	return platform_driver_register(&test_driver);
}

static void __exit my_exit(void) {
	pr_info("module exit\n");
	platform_driver_unregister(&test_driver);
	
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Longvh");
