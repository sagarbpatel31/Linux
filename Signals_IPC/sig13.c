#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	signal(SIGINT,SIG_IGN);
	signal(SIGFPE,SIG_IGN);
	while(1)
	{
		printf("In infinite loop...........\n");
		sleep(2);
	}
	return 0;
}
