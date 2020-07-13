#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/errno.h>
#include<linux/fs.h>

#define DEVICE_NAME "chardev1"
#define MAJOR_NUM 55

static int open=0;
static int chdev_open(struct inode *inode,struct file *file)
{
	if(open)	
		return -EBUSY;
	open++;
	printk(KERN_INFO "Device Opened....\n");
	try_module_get(THIS_MODULE);
	return 0;
}
static int chdev_release(struct inode *inode, struct file *file)
{
	open--;
	printk(KERN_INFO "Device file released...\n");
	module_put(THIS_MODULE);
	return 0;
}
struct file_operations devops =
{
	.owner=THIS_MODULE,
	.open=chdev_open,
	.release=chdev_release,
};
static int __init dev_init(void)
{
	int val;
	val=register_chrdev(MAJOR_NUM,DEVICE_NAME,&devops);
	if(val<0)
	{
		printk(KERN_INFO"Device file not registered...\n");
		return val;
	}
	printk(KERN_INFO "Device file successfully registered......\n");
	return 0;
}
static void __exit dev_exit(void)
{
	unregister_chrdev(MAJOR_NUM,DEVICE_NAME);
	printk(KERN_INFO "Device file successfully unregistered....\n");
}
module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sagar Patel");

