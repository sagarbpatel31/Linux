#include<linux/init.h>
#include<linux/module.h>

int mod_init(void)
{
	printk(KERN_ALERT "Inside the %s function",__FUNCTION__);
	return 0;
}
module_init(mod_init);
