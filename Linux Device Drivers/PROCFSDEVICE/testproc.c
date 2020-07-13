#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)
int main()
{
int fd,i;
int value, number;
printf("*********************************\n");
printf("*******WWW.EmbeTronicX.com*******\n");
printf("\nOpening Driver\n");
fd = open("/proc/etx_proc", O_RDWR);
if(fd < 0) {
printf("Cannot open device file...\n");
return 0;
}
printf("Enter the Values to send\n");
scanf("%d",&number);

printf("Writing Value 1 to Driver \n");
ioctl(fd, WR_VALUE, (int32_t*)&number);
printf("Reading Value 1 from Driver \n");
ioctl(fd, RD_VALUE, (int32_t*) &value);

printf("Value is %d\n", value);
printf("Closing Driver\n");
close(fd);
}
