#include <linux/init.h>
#include <linux/module.h> 
#include <linux/kernel.h>  
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/io.h>

#define DRIVER_AUTHOR "vu hai long"
#define DRIVER_DSC "button using nterrupt"


//P8.7 = GPIO2.2
//P8.8 = GPIO2.3
#define  BUTTON		2
#define  LED		3

//gpio setup  

#define GPIO2_BASE_START	0x481AC000 
#define GPIO2_BASE_STOP		0x481ACFFF 
#define GPIO_IRQSTATUS_SET_0	0x34
#define GPIO_RISINGDETECT	0x148
#define GPIO_IRQSTATUS		0x2C
#define GPIO_DATAIN		0x138
#define GPIO_DATAOUT		0x13C
#define GPIO_SETDATAOUT		0x194
#define GPIO_CLEARDATAOUT	0x190
#define GPIO_OE			0x134



//control mode
#define CONTROL_MODE_START	0x44E10000
#define CONTROL_MODE_STOP	0x44E11FFF

#define P8_7_MODE_OFFSET 	0x890
#define INPUT_PULL_DOWN		0X27 


//control interrupt
#define IRQ_CONTROL_START	0x4820000
#define IRQ_CONTROL_STOP	0x4820FFF
#define INTC_MIR_CLEAR1         0xA8
#define INTC_MIR_SET1         0xAC
#define IRQ_NUMBER		32
#define MID_OFFSET 		0



static int gpio_setup(void);
static int  interrupt_enable(void); 

static void __iomem *io;
static int irqb = 72;

static int gpio_setup(void)
{
	//set mode && enable interrupt
	unsigned int temp = 0;

	io = ioremap(CONTROL_MODE_START, CONTROL_MODE_STOP - CONTROL_MODE_START);

	if (io == NULL) {
		pr_alert("error ioremap control mode\n");
		return -1;
	}
	iowrite32(0x27, (io + P8_7_MODE_OFFSET)); 

	
	io = ioremap(GPIO2_BASE_START, GPIO2_BASE_STOP - GPIO2_BASE_START);

	if (io == NULL) {
		pr_alert("error ioremap gpio setup\n");
		return -1;
	}
	//enable interrupt signal

	iowrite32((1 << BUTTON), (io + GPIO_IRQSTATUS_SET_0));

	//choose rising

	iowrite32((1 << BUTTON), (io + GPIO_RISINGDETECT));

	//clear flag

	iowrite32((1 << BUTTON), (io + GPIO_IRQSTATUS));

	//set mode output led
	//reset state
	iowrite32(~0u, (io + GPIO_OE));
	
	temp = ioread32(io + GPIO_OE);	
	temp &= ~(1 << LED);
	iowrite32(temp, (io + GPIO_OE));
	return 0;
}

static int interrupt_enable(void)
{
	io = ioremap(IRQ_CONTROL_START, IRQ_CONTROL_STOP - IRQ_CONTROL_START);
	if (io == NULL) {
		pr_alert("error ioremap gpio setup\n");
		return -1;
	}
	iowrite32((1 << MID_OFFSET), (io + INTC_MIR_CLEAR1));

	iounmap(io);	

	return 0;
}

static irqreturn_t my_handler(int irq , void *dev_id)
{
	int timeout = 10000000;
	static int temp = 0;
	
	temp = !(temp);
	io = ioremap(GPIO2_BASE_START, GPIO2_BASE_STOP - GPIO2_BASE_START);

	if (io == NULL) {
		pr_alert("error ioremap gpio setup\n");
		return -1;
	}
	
	while ((ioread32(io + GPIO_DATAIN ) & (1 << BUTTON)) && (timeout--))
		;

	if (temp)	
		iowrite32((1 << LED), (io + GPIO_SETDATAOUT));
	else	
		iowrite32((1 << LED), (io + GPIO_CLEARDATAOUT));
	
	pr_info("my handler running ,timeout:%d\n",timeout);
	iounmap(io);
	return IRQ_HANDLED;
}
static int __init hello_init(void)
{
	pr_info("Kernel init\n");

	gpio_setup();
	//register handler
	irqb = gpio_to_irq(66);
	if (request_irq(irqb, my_handler , IRQF_TRIGGER_RISING, "longvh", NULL)){
		pr_err("requeset irq fail . can't register interrup %d\n",IRQ_NUMBER);
		return -1;
	}
	interrupt_enable();
	return 0;
}

static void __exit hello_exit(void)
{
	//unregister handler interrupt
	free_irq(irqb, NULL);
	pr_info("Goodbye\n"); 
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DSC);
