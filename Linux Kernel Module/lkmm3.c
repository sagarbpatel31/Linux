#include<linux/init.h>
#include<linux/module.h>

void mod_exit(void)
{
	printk(KERN_ALERT "Inside the %s function",__FUNCTION__);
}
module_exit(mod_exit);
