#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/kthread.h>
#include<linux/wait.h>

uint32_t read_count=0;
static struct task_struct *wait_thread;
dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
wait_queue_head_t wait_queue_etx;
int wait_queue_flag=0;

static int __init hello_init(void);
static void __exit hello_exit(void);

static int wait_function(void *unused)
{
	while(1)
	{
		printk(KERN_INFO"Waiting for Event...\n");
		wait_event_interruptible(wait_queue_etx,wait_queue_flag!=0);
		if(wait_queue_flag==2)
		{
			printk(KERN_INFO "Event came from exit function...\n");
			return 0;
		}
		printk(KERN_INFO "Event came from read function...\n");
		wait_queue_flag=0;
	}
	return 0;
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
	printk(KERN_INFO "Read Function\n");
	wait_queue_flag=1;
	wake_up_interruptible(&wait_queue_etx);
	return 0;
}
static ssize_t etx_write(struct file *filp,const char __user *buf,size_t len,loff_t *off)
{
	printk(KERN_INFO "Write Function\n");
	return 0;
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
	if((alloc_chrdev_region(&dev,0,1,"etx_dev"))<0)
	{
		printk(KERN_INFO "Cannot allocate major number...\n");
		return -1;
	}
	printk(KERN_INFO "Major = %d Minor  %d\n",MAJOR(dev),MINOR(dev));
	cdev_init(&etx_cdev,&fops);
	etx_cdev.owner =THIS_MODULE;
	etx_cdev.ops = &fops;
	if((cdev_add(&etx_cdev,dev,1))<0)
	{
		printk(KERN_INFO "Cannot add the device to the system..\n");
		goto r_class;
	}
	if((dev_class = class_create(THIS_MODULE,"etx_class"))==NULL)
	{
		printk(KERN_INFO "Cannot create the struct class..\n");
		goto r_class;
	}
	if((device_create(dev_class,NULL,dev,NULL,"etx_device"))==NULL)
	{
		printk(KERN_INFO"Cannot create the Device....\n");
		goto r_device;
	}
	init_waitqueue_head(&wait_queue_etx);
	wait_thread=kthread_create(wait_function,NULL,"WaitThread");
	if(wait_thread)
	{
		printk(KERN_INFO"Thread Created Successfully....\n");
		wake_up_process(wait_thread);
	}
	else
	{
		printk(KERN_INFO "Thread Creation failed...\n");
	}
	printk(KERN_INFO "Device Driver Insert DOne.....\n");
	return 0;
	r_device:
		class_destroy(dev_class);
	r_class:
		unregister_chrdev_region(dev,1);
		return -1;
}
void __exit hello_exit(void)
{
	wait_queue_flag=2;
	wake_up_interruptible(&wait_queue_etx);
	device_destroy(dev_class,dev);	
	class_destroy(dev_class);
	cdev_del(&etx_cdev);
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO"Device Driver Remove...\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAGAR PATEL");
MODULE_DESCRIPTION("Waitqueue");
