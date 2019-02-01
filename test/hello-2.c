#include <linux/init.h>
#include <linux/module.h> 
#include <linux/kernel.h>  
#include <linux/kdev_t.h>  // for macro MAJOR MINOR 
#include <linux/fs.h>      // for function register major , minor
#include <linux/types.h>   // for dev_t type
#include <linux/device.h>   // for dev_t type
#include <linux/cdev.h>
#include <linux/io.h>

#define DRIVER_AUTHOR "vu hai long"
#define DRIVER_DSC "device driver file example"

#define PRM_WKUP_START 0x44E00D00
#define PRM_WKUP_STOP  0x44E00DFF

#define CM_WKUP_START  0x44E00400
#define CM_WKUP_STOP   0x44E004FF

//30002h
#define CM_WKUP_WDT1_CLKCTRL 0xD4 
//8h 
#define PM_WKUP_PWRSTCTRL    0x4   

static void __iomem *io;
static int __init hello_init(void)
{
	unsigned long temp = 0;
	printk(KERN_EMERG "Device driver file example \n");
	
	io = ioremap(PRM_WKUP_START , (PRM_WKUP_STOP- PRM_WKUP_START));

	temp = ioread32(io + PM_WKUP_PWRSTCTRL) ; 
	
	temp = ioread32(io + PM_WKUP_PWRSTCTRL) ; 
	printk(KERN_EMERG "pm_wkup : 0x%X\n" , temp);
	
	io = ioremap(CM_WKUP_START , (CM_WKUP_STOP - CM_WKUP_START));
	
	temp = ioread32(io + CM_WKUP_WDT1_CLKCTRL ) ; 
	temp |= 0x02;
	iowrite32( temp ,  (io + CM_WKUP_WDT1_CLKCTRL));

	temp = ioread32(io + CM_WKUP_WDT1_CLKCTRL ) ; 
	
	printk(KERN_EMERG "cm_wkup  : 0x%X\n" , temp);


	iounmap(io);
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_EMERG "Goodbye\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DSC);
