#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/interrupt.h>    /* for tasklets API */ 
#include <linux/mutex.h>    /* for tasklets API */ 
 
char tasklet_data[]="We use a string; but it could be pointer to a structure"; 
  
/* Tasklet handler, that just print the data */ 
struct mutex my_mutex;
void tasklet_function(unsigned long data) 
{ 
	mutex_lock(&my_mutex);
	 printk("%s\n", (char *)data); 
	mutex_unlock(&my_mutex);
} 
	   
DECLARE_TASKLET(my_tasklet, tasklet_function, (unsigned long) tasklet_data); 

static int __init my_init(void) 
{ 
    /* 
	    * Schedule the handler. 
		*Tasklet are also scheduled from interrupt handler 
   */ 
   	mutex_init(&my_mutext);
	tasklet_schedule(&my_tasklet); 
    return 0; 
} 
		    
void my_exit(void) 
{ 
    tasklet_kill(&my_tasklet); 
} 
	 
module_init(my_init); 
module_exit(my_exit); 
MODULE_AUTHOR("John Madieu <john.madieu@gmail.com>"); 
MODULE_LICENSE("GPL"); 
