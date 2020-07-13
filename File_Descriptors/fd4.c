#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int fd,fd1;
	char str[20];
	close(2);
	fd=open("data",O_RDONLY|O_CREAT);
	fd1=open("data1",O_RDONLY|O_CREAT);
	perror("open");
	printf("fd = %d\n",fd);
	printf("fd1 = %d\n",fd1);

}
