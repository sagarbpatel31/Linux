#include<linux/init.h>
#include<linux/module.h>

int simple_module_init(void)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	printk(KERN_ALERT "Hello World\n");
	return 0;
}

void simple_module_exit(void)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	printk(KERN_ALERT "Goodbye....\n");
}

module_init(simple_module_init);
module_exit(simple_module_exit);

