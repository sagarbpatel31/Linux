#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kdev_t.h>
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Character Device Example");
MODULE_AUTHOR("Sagar Patel");
// All the file operations which the driver will be able to handle
ssize_t char_read(struct file *, char *, size_t, loff_t *);
ssize_t char_write(struct file *, const char *, size_t, loff_t *);
int char_open(struct inode *, struct file *);
int char_release(struct inode *, struct file *);
char str[100];
// Defining the structure containing all file operations for the driver
static struct file_operations fops = { .owner = THIS_MODULE, .read = char_read,
.write = char_write, .open = char_open, .release = char_release, };
// Assigning major number for the driver dynamically by the kernel
static int major = 0;
// Name/Entry of the kernel module in /proc/devices
static const char dev_name[] = "my_test_char_driver";
// Registering the device
static int register_device(void) {
int res;
printk(KERN_NOTICE "CharDriver: register_device() initiated\n");
res = register_chrdev(0, dev_name, &fops);
if (res < 0) {
printk(KERN_ALERT "CharDriver: device registration failed!\n");
return res;
}
major = res; //Returning the major number assigned by the kernel
printk(KERN_NOTICE "CharDriver: registered as a char device with major number #%d\n", major);
return 0;
}
// Unregistering the device
void unregister_device(void) {
printk(KERN_NOTICE "CharDriver: unregister_device() initiated\n");
if (major != 0)
unregister_chrdev(major, dev_name);
}
// Reading operation of the driver
ssize_t char_read(struct file *fp, char __user *buf, size_t count, loff_t *fpos)
{
int len=10;
char* mystr;
printk(KERN_NOTICE "CharDriver: char_read() initiated\n");
printk(KERN_NOTICE " %s \n",str);
if (count <len)
return -EINVAL;
//if (*fpos != 0)
if (*fpos>len)
return -EINVAL;
if (!access_ok(VERIFY_WRITE, buf, count))
return -EFAULT;
//*fpos += 10;
mystr = str + *fpos;
if (copy_to_user(buf, mystr, len))
return -EINVAL;
*fpos += len;
return len;
}
// Writing operation of the driver
ssize_t char_write(struct file *fp, const char __user *buf, size_t count, loff_t *fpos)
{
int len = 100;
printk(KERN_INFO "CharDriver: write called..\n");
if (count >len)
return -EINVAL;
if (!access_ok(VERIFY_READ, buf, count))
return -EFAULT;
if (copy_from_user(str,buf, count))
return -EINVAL;
printk(KERN_INFO "CharDriver: value written into device is: %s", str);
return count;
}
// Open operation of the driver
int char_open(struct inode *node, struct file *fp) {
printk(KERN_NOTICE "CharDriver: open is called\n");
return 0;
}
// Close/Release operation of the driver
int char_release(struct inode *node, struct file *fp) {
printk(KERN_NOTICE "CharDriver: release is called\n");
return 0;
}
// Initialization function of kernel module i.e. this char driver
static int char_init(void) {
printk(KERN_ALERT "CharDriver: Init\n");
return register_device(); //Registering region with major no & minor no
}
// Exit function of kernel module i.e. this char driver
static void char_exit(void) {
unregister_device(); //Unregistering the allocation
printk(KERN_ALERT "CharDriver: Bye\n");
}
module_init(char_init);
module_exit(char_exit);
