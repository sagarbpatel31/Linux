#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/device.h>
#include<linux/cdev.h>

dev_t dev=0;
static struct class *dev_class;
static struct cdev etx_cdev;
int exdev_open(struct inode *pinode,struct file *pfile)
{
	printk(KERN_ALERT " Inside the %s function \n",__FUNCTION__);
	return 0;
}
ssize_t exdev_read(struct file *pfile,char __user *buffer,size_t length,loff_t *offset)
{

	printk(KERN_ALERT " Inside the %s function \n",__FUNCTION__);
	return 0;
}
ssize_t exdev_write(struct file *pfile,const char __user *buffer,size_t length,loff_t *offset)
{

	printk(KERN_ALERT " Inside the %s function \n",__FUNCTION__);
	return length;
}
int exdev_close(struct inode *pinode,struct file *pfile)
{

	printk(KERN_ALERT " Inside the %s function \n",__FUNCTION__);
	return 0;
}

struct file_operations fops={
	.owner = THIS_MODULE,
	.open = exdev_open,
	.read = exdev_read,
	.write = exdev_write,
	.release = exdev_close,	
};
static int __init hello_init(void)
{
	if((alloc_chrdev_region(&dev,0,1,"Sample Char Device Driver"))<0)
	{
		printk(KERN_INFO "Cannot allocate major number for device 1\n");
		return -1;
	}
	printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
	
	cdev_init(&etx_cdev,&fops);
	if((cdev_add(&etx_cdev,dev,1))<0)
	{
		printk(KERN_INFO "Cannot add the device to the system..\n");
		goto r_class;
	}	

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
	cdev_del(&etx_cdev);
	printk(KERN_INFO "Kernel Module Removed Successfully.......\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");

MODULE_DESCRIPTION("CHARACTER DRIVER");
MODULE_AUTHOR("SAGAR PATEL ");

