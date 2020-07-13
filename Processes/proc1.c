#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	int id;
	if(fork())
	{
		while(1)
		{
			printf("In parent, PID = %d\n",getpid());
			sleep(3);	
		}
	}
	else
	{
		while(1)
		{
			printf("In child, PID = %d\n",getpid());
			sleep(4);
		}
	}
	return 0;
}
