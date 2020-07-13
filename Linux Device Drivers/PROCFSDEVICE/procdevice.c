#include "header.h"

int32_t value = 0;
static int len =1;
char arr[20]="Sagar Patel\n";
static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);

static int proc_open(struct inode *inode, struct file *file);
static int proc_release(struct inode *inode, struct file *file);
static ssize_t proc_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t proc_write(struct file *filp, const char *buf, size_t len, loff_t * off);

static struct file_operations proc_fops =
{
.read = proc_read,
.write = proc_write,
.open = proc_open, 
.release = proc_release,
};

static int proc_open(struct inode *inode,struct file *file)
{
	printk(KERN_INFO "Proc file opened....\n");
	return 0;
}
static int proc_release(struct inode *inode,struct file *file)
{
	printk(KERN_INFO "Proc File Released..\n");
	return 0;
}
static ssize_t proc_read (struct file *filp,char __user *buffer,size_t length,loff_t *offset)
{
	printk(KERN_INFO "Proc File Read..\n");
	if(len)
		len=0;
	else
	{
		len=1;
		return 0;
	}
	copy_to_user(buffer,arr,sizeof(arr));
	return length;
}
static ssize_t proc_write (struct file *filp,const char *buff,size_t len,loff_t *off)
{
	printk(KERN_INFO "Proc file wrote..\n");
	copy_from_user(arr,buff,len);
	return len;
}


static int __init etx_driver_init(void)
{


proc_create("etx_proc",0666,NULL,&proc_fops);

printk(KERN_INFO "Device Driver Insert...Done!!!\n");


return 0;
}
void __exit etx_driver_exit(void)
{

remove_proc_entry("etx_proc",NULL);
}
module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sagar Patel");
MODULE_DESCRIPTION("A simple device driver");
MODULE_VERSION("1.5");
