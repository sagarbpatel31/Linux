#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

volatile int rd ;
volatile int wr;
int main()
{
	int fd;
	int option;
	printf("***************\n");
	printf("****Welcome****\n");
	fd=open("/sys/kernel/etx_sysfs",O_RDWR);
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
			 printf("Enter the number to write into the driver:\n");
			 scanf("%s",wr); 
			 printf("Data writing.......\n");
			 write(fd,wr,strlen(wr)+1);
			 printf("Write Done....\n");
			 break;
			case 2:
			 printf("Data Reading..\n");
			 read(fd,rd,1024);
			 printf("Read Done..\n");
			 printf("Data = %s\n",rd);
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
