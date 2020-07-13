#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

void main()
{
	int fd[2];
	pipe(fd);	
	if(fork())
	{
		char s1[10],s2[10];
		printf("Enter the string for child...\n");
		scanf("%s",s1);
		write(fd[1],s1,strlen(s1)+1);
		printf("Enter another message ...\n");
		scanf("%s",s2);
		write(fd[1],s2,strlen(s2)+1);
	}
	else
	{
		char s3[10],s4[10];
		read(fd[0],s3,sizeof(s3));
		printf("Message: %s\n",s3);
		read(fd[0],s4,sizeof(s4));
		printf("Another message: %s\n",s4);
	}
}
