#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	pid_t p = fork();
	if(p==0)
	{
		while(1)
		{
			printf("Infinite loop...\n");
			sleep(1);
		}
	}
	else
	{
		sleep(4);
		kill(p,SIGSEGV);
		printf("I have killed my child....\n");
	}
	return 0;
}
