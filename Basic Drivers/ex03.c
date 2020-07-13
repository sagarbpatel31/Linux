#include<linux/kernel.h> 
#include<linux/init.h> 
#include<linux/module.h> 
static int __init hello_world_init(void) 
{ 
        printk(KERN_INFO "Hello World...This is simple driver module\n");
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
MODULE_DESCRIPTION("A simple linux driver module"); 
MODULE_VERSION("1.1"); 
