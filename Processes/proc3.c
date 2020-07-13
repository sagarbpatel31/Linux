#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	if(mkfifo("/tmp/test_fifo",0666)!=0)
		perror("mkfifo")
	if(mkfifo("/tmp/test_fifo",0666)!=0)
		perror("mkfifo")
	return 0;
		

}
