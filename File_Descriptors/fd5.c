#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int fd;
	fd=open("data",O_WRONLY|O_CREAT|O_TRUNC,0644);
	write(fd,"Hello World\n",strlen("Hello World\n"));	
	printf("Write done.......\n");
	close(fd);
	return 0;
}
