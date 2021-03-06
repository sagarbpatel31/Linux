#include<linux/kernel.h> 
#include<linux/init.h> 
#include<linux/module.h> 
#include<linux/moduleparam.h>

int value,arr_value[4];
char *name;
int cb_value=0;

module_param(value,int,S_IRUSR|S_IWUSR);
module_param(name,charp,S_IRUSR|S_IWUSR);
module_param_array(arr_value,int,NULL,S_IRUSR|S_IWUSR);

int notify_param(const char *v,const struct kernel_param *kp)
{
	int res = param_set_int(v,kp);
	if(res==0)
	{
		printk(KERN_INFO "Callback function called.......\n");
		printk(KERN_INFO "New value of cb_value = %d\n",cb_value);
		return 0;
	}
	return -1;
}
const struct kernel_param_ops my_param =
{
	.set = &notify_param,
	.get = &param_get_int,
};

module_param_cb(cb_value,&my_param,&cb_value,S_IRUGO|S_IWUSR);

static int __init hello_world_init(void) 
{ 
	int i;
        printk(KERN_INFO "Value = %d\n",value); 
        printk(KERN_INFO "cb_value = %d\n",cb_value); 
        printk(KERN_INFO "Name = %s\n",name);
	for(i=0;i<(sizeof arr_value/sizeof(int));i++)
	{
		printk(KERN_INFO "Arr_value[%d] =%d\n",i,arr_value[i]); 
	}
        printk(KERN_INFO "Kernel Module Inserted Successfully...\n"); 
	return 0; 
}  

void __exit hello_world_exit(void) 
{ 
	printk(KERN_INFO "Goodbye World....\n");
	printk(KERN_INFO "Kernel Module Removed Successfully...\n"); 
} 
module_init(hello_world_init); 
module_exit(hello_world_exit); 

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("SAGAR PATEL"); 
MODULE_DESCRIPTION("A module parameter used linux driver module"); 
MODULE_VERSION("1.1"); 
