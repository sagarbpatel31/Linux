#include "header.h"

#define IRQ_NO 11

void tasklet_fn(unsigned long);
DECLARE_TASKLET(tasklet,tasklet_fn,1);
void tasklet_fn(unsigned long arg)
{
	printk(KERN_INFO "Executing Tasklet Function: arg = %ld\n",arg);
}
static irqreturn_t irq_handler(int irq,void *dev_id)
{
	printk(KERN_INFO "Shared IRQ: Interrupt 11 occurred...\n");
 	tasklet_schedule(&tasklet);	
	return IRQ_HANDLED;
}

dev_t dev =0;

static struct class *dev_class;
static struct cdev etx_cdev;

static int __init hello_init(void);
static void __exit hello_exit(void);


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
	asm("int $0x3B");
	return 0;
}
static ssize_t etx_write(struct file *filp,const char __user *buf,size_t len,loff_t *off)
{
	printk(KERN_INFO "Data write function...\n");
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
	if(request_irq(IRQ_NO,irq_handler,IRQF_SHARED,"my_device",(void *)(irq_handler)))
	{
		printk(KERN_INFO "my device cannot register IRQ...\n");
		goto irq;	
	}	
	printk(KERN_INFO "Device Driver Insert Done successfully....\n");
	return 0;
	
	irq:
		free_irq(IRQ_NO,(void *)(irq_handler));
	r_device:
		class_destroy(dev_class);
	r_class:
		unregister_chrdev_region(dev,1);
		return -1;
}
void __exit hello_exit(void)
{
	tasklet_kill(&tasklet);	
	free_irq(IRQ_NO,(void *)(irq_handler));
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
