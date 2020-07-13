#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/device.h>

dev_t dev=0;
static struct class *dev_class;

static int __init hello_init(void)
{
	if((alloc_chrdev_region(&dev,0,1,"Sample Char Device Driver"))<0)
	{
		printk(KERN_INFO "Cannot allocate major number for device \n");
		return -1;
	}
	printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));

	if((dev_class=class_create(THIS_MODULE,"my_class"))==NULL)
	{
		printk(KERN_INFO"Cannot create the struct class for device...\n");
		goto r_class;
	}	
	
	if((device_create(dev_class,NULL,dev,NULL,"my_device"))==NULL)
	{
		printk(KERN_INFO "Cannot create the device....\n");
		goto r_device;
	}
	printk(KERN_INFO "Kernel module inserted successfully......\n");
	return 0;
	r_device:
		class_destroy(dev_class);
	r_class:
		unregister_chrdev_region(dev,1);
		return -1;
}
void __exit hello_exit(void)
{
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	unregister_chrdev_region(dev,1);	
	printk(KERN_INFO "Kernel Module Removed Successfully.......\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAGAR PATEL");
MODULE_DESCRIPTION("Automatically creating the device file");
MODULE_VERSION("1.1");
