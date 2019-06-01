#include <linux/module.h>
#include <linux/device.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <linux/spi/spi.h>
static int mpu_probe(struct spi_device *pdev) {
	
	int ret ;
	pr_info("jump to probe\n");	
	
	return 0;
}
static int mpu_remove(struct spi_device *pdev) {
	pr_info("jump to remove\n");
	
	return 0;
}

static const struct of_device_id mpu_match_of[] = {

	{ .compatible= "testlongvh12", },
	{}
};

MODULE_DEVICE_TABLE(of, mpu_match_of);

static struct spi_driver mpu_driver = {
	.driver = {
		.name = "mpu_driver",
		.of_match_table = mpu_match_of,
	},
	.probe = mpu_probe,
	.remove = mpu_remove,
};


module_spi_driver(mpu_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LONGVH");
MODULE_DESCRIPTION("SIMPLE SPI DRIVER");
