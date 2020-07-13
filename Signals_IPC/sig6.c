#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void shandler(int signum)
{
	printf("Hey I got the signal...%d\n",signum);
	for(int i=0;i<5;i++)
	{
		printf("Masking for 5 seconds..\n");
		sleep(1);
	}
	printf("Done...\n");
	sleep(2);
}
int main()
{
	struct sigaction s;
	s.sa_handler=shandler;
	s.sa_flags=0;	
	sigfillset(&s.sa_mask);
	sigaction(SIGINT,&s,NULL);
	while(1)
	{
		printf("Infinite loop .......\n");
		sleep(1);
	}
	return 0;
}
