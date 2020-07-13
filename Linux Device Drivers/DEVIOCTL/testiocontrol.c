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
int value[2], number[2];
printf("*********************************\n");
printf("\nOpening Driver\n");
fd = open("/dev/etx_device", O_RDWR);
if(fd < 0) {
printf("Cannot open device file...\n");
return 0;
}
printf("Enter the Values to send\n");
for(i=0;i<2;i++)
{
	scanf("%d",&number[i]);
}
printf("Writing Value 1 to Driver \n");
ioctl(fd, WR_VALUE, (int32_t*)&number[0]);
printf("Reading Value 1 from Driver \n");
ioctl(fd, RD_VALUE, (int32_t*) &value[0]);

printf("Writing Value 2 to Driver \n");
ioctl(fd, WR_VALUE, (int32_t*)&number[1]);
printf("Reading Value 2 from Driver \n");
ioctl(fd, RD_VALUE, (int32_t*) &value[1]);

printf("Values are %d and %d\n", value[0],value[1]);
printf("Closing Driver\n");
close(fd);
}
