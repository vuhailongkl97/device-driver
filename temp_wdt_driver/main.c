#include <linux/init.h>
#include <linux/module.h> 
#include <linux/kernel.h>  
#include <linux/kdev_t.h>  // for macro MAJOR MINOR 
#include <linux/fs.h>      // for function register major , minor

#include <linux/miscdevice.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/uaccess.h>


#include <linux/watchdog.h>

#include "ports.h"

#define DRIVER_AUTHOR "vu hai long"
#define DRIVER_DSC "device driver file example"

#define WDT_START 0x44E35000
#define WDT_STOP  0x44E35FFF

#define PRM_WKUP_START 0x44E00D00
#define PRM_WKUP_STOP  0x44E00DFF

#define CM_WKUP_START  0x44E00400
#define CM_WKUP_STOP   0x44E004FF

//30002h
#define CM_WKUP_WDT1_CLKCTRL 0xD4 
//8h 
#define PM_WKUP_PWRSTCTRL    0x4   

#define WATCHDOG_REV		(0x00)
#define WATCHDOG_SYS_CONFIG	(0x10)
#define WATCHDOG_STATUS		(0x14)
#define WATCHDOG_CNTRL		(0x24)
#define WATCHDOG_CRR		(0x28)
#define WATCHDOG_LDR		(0x2c)
#define WATCHDOG_TGR		(0x30)
#define WATCHDOG_WPS		(0x34)
#define WATCHDOG_SPR		(0x48)
void __iomem *io;
static void disable_wdt(void)
{
		
	unsigned int temp = 0 ;
	io = ioremap( WDT_START , (WDT_STOP -WDT_START));
	
	iowrite32( 0xAAAA , (io + WATCHDOG_SPR));
	do {
	
		temp = readl_relaxed(io +  WATCHDOG_WPS)  & ( 1 << 4 ) ;
	}
	while (temp);
	iowrite32( 0x5555 , (io + WATCHDOG_SPR));
	do {
	
		temp = readl_relaxed(io +  WATCHDOG_WPS)  & ( 1 << 4 ) ;
	}
	while (temp);
}
static void enable_wdt(void)
{
	unsigned int temp = 0 ;
	io = ioremap( WDT_START , (WDT_STOP -WDT_START));
	
	iowrite32( 0xBBBB , (io + WATCHDOG_SPR));
	do {
	
		temp = ioread32(io +  WATCHDOG_WPS)  & ( 1 << 4 ) ;
	}
	while (temp);
	iowrite32( 0x4444 , (io + WATCHDOG_SPR));
	do {
	
		temp = ioread32(io +  WATCHDOG_WPS)  & ( 1 << 4 ) ;
	}
	while (temp);
	
}
static void enable_power_wdt(void)
{
	unsigned long temp = 0;
	printk(KERN_EMERG "Driver WTD \n");
	
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
	
}
static int __init hello_init(void)
{
	unsigned int temp = 0 ;
	enable_power_wdt();
	printk(KERN_EMERG "OK ENABLE POWER \n");
	disable_wdt();
	printk(KERN_EMERG "OK disable wdt \n");

	io = ioremap( WDT_START , (WDT_STOP -WDT_START));

	//init prescale
	while( ioread32( io +  WATCHDOG_WPS) & ( 1 << 0 ));

	iowrite32( (1 << 5) | ( 1 << 2),(io +  WATCHDOG_CNTRL) );
	
	while( ioread32( io +  WATCHDOG_WPS) & ( 1 << 0 ));

	printk(KERN_EMERG "OK init prescale \n");

	// set time   out <> Wdt_lrd
	
	
	while( ioread32( io +  WATCHDOG_WPS) & ( 1 << 2 ));
	iowrite32( 0xFFFF0000 , (io + WATCHDOG_LDR));
	while( ioread32( io +  WATCHDOG_WPS) & ( 1 << 2 ));
	
	printk(KERN_EMERG "OK set timeout \n");
	// trigger  for restart count 
	temp = ioread32(io + WATCHDOG_TGR);	

	while( ioread32( io +  WATCHDOG_WPS) & ( 1 << 3 ));
	iowrite32( ~temp  , (io + WATCHDOG_TGR));
	while( ioread32( io +  WATCHDOG_WPS) & ( 1 << 3 ));

	printk(KERN_EMERG "OK trigger  \n");
	enable_wdt();
	printk(KERN_EMERG "OK enable wdt  \n");
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


