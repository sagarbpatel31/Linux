#include "header.h"

#define mem_size 1024
#define TIMEOUT 5000

static struct timer_list my_timer;
static unsigned int count =0;
dev_t dev =0;

static struct class *dev_class;
static struct cdev etx_cdev;

uint8_t *kernel_buffer;

static int __init hello_init(void);
static void __exit hello_exit(void);

void timer_callback(unsigned long data)
{
	printk(KERN_INFO "Timer Callback Function Called [%d]\n",count++);
	mod_timer(&my_timer,jiffies+msecs_to_jiffies(TIMEOUT));
}	

static int etx_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Device File Opened succesfully....\n");
	return 0;
}
static int etx_release(struct inode *inode,struct file *file)
{
	printk(KERN_INFO "Device File Closed successfully..\n");
	return 0;
}
static ssize_t etx_read(struct file *filp,char __user *buf,size_t len,loff_t *off)
{
	printk(KERN_INFO "Data Read: Done..\n");
	return mem_size;
}
static ssize_t etx_write(struct file *filp,const char __user *buf,size_t len,loff_t *off)
{
	printk(KERN_INFO "Data write Done...\n");
	return len;
}

static struct file_operations fops=
{
	.owner =THIS_MODULE,
	.read = etx_read,
	.write = etx_write,
	.open = etx_open,
	.release = etx_release,
};

static int __init hello_init(void)
{
	if((alloc_chrdev_region(&dev,0,1,"Device"))<0)
	{
		printk(KERN_INFO "Cannot allocate major numbers...\n");
		return -1;
	}	
	printk(KERN_INFO "Major = %d Minor = %d\n",MAJOR(dev),MINOR(dev));
	cdev_init(&etx_cdev,&fops);
	
	if((cdev_add(&etx_cdev,dev,1))<0)
	{
		printk(KERN_INFO "Cannot add the device to the system..\n");
		goto r_class;
	}
	if((dev_class=class_create(THIS_MODULE,"my_class"))==NULL)
	{
		printk(KERN_INFO "Cannot create the struct class.....\n");
		goto r_class;
	}
	if((device_create(dev_class,NULL,dev,NULL,"my_device"))==NULL)
	{
		printk(KERN_INFO "Cannot create the device.....\n");
		goto r_device;
	}
	setup_timer(&my_timer,timer_callback,0);
	mod_timer(&my_timer,jiffies+msecs_to_jiffies(TIMEOUT));

	printk(KERN_INFO "Device Driver Insert Done successfully....\n");
	return 0;
	
	r_device:
		class_destroy(dev_class);
	r_class:
		unregister_chrdev_region(dev,1);
		return -1;
}
void __exit hello_exit(void)
{
	del_timer(&my_timer);
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	cdev_del(&etx_cdev);
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "Device Driver Remove Done successfully.....\n");

}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sagar B Patel");
MODULE_DESCRIPTION("Character Real Device");
MODULE_VERSION("1.4");	
