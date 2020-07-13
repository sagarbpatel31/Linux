#include "header.h"

uint32_t read_count=0;
dev_t dev =0;
int completion_flag =0;
struct completion my_complete;
static struct class *dev_class;
static struct cdev etx_cdev;
static struct task_struct *ethread;
static int __init hello_init(void);
static void __exit hello_exit(void);

int wait_function (void *pv)
{
	while(1)
	{
		printk(KERN_INFO"Waiting for event...\n");
		wait_for_completion(&my_complete);
		if(completion_flag==2)
		{
			printk(KERN_INFO "Event came from Exit function.....\n");
			return 0;
		}
		printk(KERN_INFO "Event came from Read Function......%d..\n",++read_count);
		completion_flag=0;
	}
	do_exit(0);
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
	completion_flag=1;
	if(!completion_done(&my_complete))
	{
		complete(&my_complete);
	}
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
	
	ethread=kthread_create(wait_function,NULL,"threadd");
	if(ethread)
	{
		printk(KERN_INFO "Thread created successfully......\n");
		wake_up_process(ethread);
	}
	else
	{
		printk(KERN_INFO "Cannot create kthread....\n");
		goto r_device;
	}
	init_completion(&my_complete);
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
	completion_flag=2;
	if(!completion_done(&my_complete))
	{
		complete(&my_complete);
	}
	
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
