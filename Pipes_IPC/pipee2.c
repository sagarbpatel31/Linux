#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
void main()
{
	int fd[2],fd1[2];
	pipe(fd);
	pipe(fd1);	
	if(fork())
	{
		char s1[10],s2[10];
		printf("Enter the string for child...\n");
		scanf("%s",s1);
		write(fd[1],s1,strlen(s1)+1);
		read(fd1[0],s2,sizeof(s2));
		printf("String from child:.%s\n",s2);
	}
	else
	{
		char str1[10],str2[10];
		read(fd[0],str1,sizeof(str1));
		printf("Message from parent: %s\n",str1);
		printf("\nEnter message for parent..\n");
		scanf("%s",str2);
		write(fd1[1],str2,strlen(str2)+1);	
	}
}
