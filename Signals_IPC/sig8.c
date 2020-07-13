#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void shandler(int signum)
{
	printf("Hey I got the signal...%d\n",signum);
}
int main()
{
	signal(SIGINT,shandler);
	while(1)
	{
		printf("Infinite loop .......\n");
		sleep(1);
	}
	return 0;
}
