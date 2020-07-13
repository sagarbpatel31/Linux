#include "header.h"
char task[]="Hello Friends!";
void tf(unsigned long data)
{
	printk(KERN_INFO "data = %s\n",(char *)data);
	
}
DECLARE_TASKLET(my_tasklet,tf,(unsigned long)task);
static __init int sample_init(void)
{
	tasklet_schedule(&my_tasklet);
	return 0;
}
static __exit void sample_exit(void)
{
	tasklet_kill(&my_tasklet);
}
module_init(sample_init);
module_exit(sample_exit);
