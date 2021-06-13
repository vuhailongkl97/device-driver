#include <linux/module.h>
#include <linux/device.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <linux/spi/spi.h>
#include <linux/of.h>
static int mpu_probe(struct spi_device *pdev) {
	
	int ret ;
	pr_alert("jump to probe\n");	
	
	return 0;
}
static int mpu_remove(struct spi_device *pdev) {
	pr_alert("jump to remove\n");
	
	return 0;
}
#ifdef CONFIG_OF
static const struct of_device_id mpu_match_of[] = {

	{ .compatible= "hea,long", },
	{},
};
MODULE_DEVICE_TABLE(of, mpu_match_of);
#endif
static struct spi_driver mpu_driver = {
	.driver = {
		.owner = THIS_MODULE,
		.name = "mpu",
		.of_match_table = mpu_match_of,
	},
	.probe = mpu_probe,
	.remove = mpu_remove,
};

module_spi_driver(mpu_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LONGVH");
MODULE_DESCRIPTION("SIMPLE SPI DRIVER");
