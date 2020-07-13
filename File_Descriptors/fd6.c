#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	char a[20] = "";
	int fd;
	fd=open("data",O_RDONLY);
	read(fd,&a,20);
	printf("Data = %s\n",a);
	close(fd);
}
