#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kernel.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/slab.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#include<linux/init.h>
#include<linux/ioctl.h>
#include<linux/sysfs.h>
#include<linux/kobject.h>
#include<linux/interrupt.h>
#include<asm/io.h>
#include<linux/list.h>

