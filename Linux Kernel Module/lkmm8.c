#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

int user_function(void);

static __init int simple_module_init(void)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	user_function();
	return 0;
}

static __exit void simple_module_exit(void)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	printk(KERN_ALERT "Goodbye\n");
}

module_init(simple_module_init);
module_exit(simple_module_exit);

