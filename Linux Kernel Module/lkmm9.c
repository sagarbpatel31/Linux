#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("GPL");

int count =1;
module_param(count,int,0);

static __init int simple_module_init(void)
{
	unsigned int i;
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	for(i=0;i<count;i++)
	{
		printk(KERN_ALERT "Number: %d \n",i);
	}	

	return 0;
}

static __exit void simple_module_exit(void)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	printk(KERN_ALERT "Goodbye\n");
}

module_init(simple_module_init);
module_exit(simple_module_exit);

