#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int8_t write_buf[1024];
int8_t read_buf[1024];

int main()
{
	int fd;
	int option;
	printf("***************\n");
	printf("****Welcome****\n");
	fd=open("/proc/etx_proc",O_RDWR);
	if(fd<0)
	{
		printf("Cannot open Device fie....\n");
		return 0;
	}
	while(1)
	{
		printf("**Please Enter Option***\n");	
		printf("   1. Write    \n");
		printf("   2. Read\n");
		printf("   3. Exit\n");
		scanf("%d",&option);
		printf("Option = %d\n",option);
		switch(option)
		{
			case 1:
			 printf("Enter the string to write into the driver:\n");
			 scanf("%s",write_buf);
			 printf("Data writing.......\n");
			 write(fd,write_buf,strlen(write_buf)+1);
			 printf("Write Done....\n");
			 break;
			case 2:
			 printf("Data Reading..\n");
			 /* Reverse the string */
			 read(fd,read_buf,1024);
			 printf("Read Done..\n");
			 printf("Data = %s\n",read_buf);
			 break;
			case 3:
			 close(fd);
			 exit(1);
			 break;
			default:
			 printf("Enter the valid option....\n");
			 break;
		}
	}
	close(fd);
}
