#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	sigset_t newset,oldset;
	sigemptyset(&newset);
	sigaddset(&newset,SIGINT);
	sigprocmask(SIG_SETMASK,&newset,&oldset);
	int i=0;
	for(i=1;i<=5;i++)
	{
		printf("I am masking SIGINT for 5 seconds....\n");
		sleep(1);
	}
	sigprocmask(SIG_SETMASK,&oldset,NULL);
	for(i=1;i<=5;i++)
	{
		printf("Again old mask..........\n");
		sleep(1);
	}
	return 0;
}
