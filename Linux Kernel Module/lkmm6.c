#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

static int data __initdata = 5;

static __init int simple_module_init(void)
{
	unsigned int i;
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	for(i=0;i<data;i++)
	{
		printk(KERN_ALERT "Number: %d \n",data);
	}	

        printk(KERN_ALERT "Hello World %d \n",data);
	return 0;
}

static __exit void simple_module_exit(void)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	printk(KERN_ALERT "Goodbye\n");
}

module_init(simple_module_init);
module_exit(simple_module_exit);

