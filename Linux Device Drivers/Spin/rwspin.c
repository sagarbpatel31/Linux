#include "header.h"
static DEFINE_RWLOCK(my_rwlock);

dev_t dev =0;
unsigned long etx_global_variable = 0;

static struct class *dev_class;
static struct cdev etx_cdev;

static struct task_struct *ethread1;
static struct task_struct *ethread2;

static int __init hello_init(void);
static void __exit hello_exit(void);

int thread_function1(void *pv)
{
	while(!kthread_should_stop())
	{
		write_lock(&my_rwlock);
		etx_global_variable++;
		write_unlock(&my_rwlock);
		msleep(1000);	
	}
	return 0;
}
int thread_function2(void *pv)
{
	while(!kthread_should_stop())
	{
		read_lock(&my_rwlock);
		printk(KERN_INFO "In thread function2 ..%lu\n",etx_global_variable);
		read_unlock(&my_rwlock);
		msleep(1000);	
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
	printk(KERN_INFO "Data Read function..\n");
	return 0;
}
static ssize_t etx_write(struct file *filp,const char __user *buf,size_t len,loff_t *off)
{
	printk(KERN_INFO "Data write function...\n");
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
	
	ethread1=kthread_run(thread_function1,NULL,"threadd1");
	if(ethread1)
	{
		printk(KERN_ERR "Thread1 Created Successfully..\n");
	}
	else
	{
		printk(KERN_INFO "Cannot create kthread1....\n");
		goto r_device;
	}
	ethread2=kthread_run(thread_function2,NULL,"threadd2");
	if(ethread2)
	{
		printk(KERN_ERR "Thread2 Created Successfully..\n");
	}
	else
	{
		printk(KERN_INFO "Cannot create kthread2....\n");
		goto r_device;
	}
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
	kthread_stop(ethread1);
	kthread_stop(ethread2);
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
