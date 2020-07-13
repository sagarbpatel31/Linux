#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void shandler1(int signum)
{
	printf("Hey I got the signal...%d\n",signum);
	signal(SIGINT,SIG_DFL);
}
void shandler2(int signum)
{
        printf("Hey I got the signal...%d\n",signum);
        signal(SIGQUIT,SIG_DFL);
}
void shandler3(int signum)
{
        printf("Hey I got the signal...%d\n",signum);
        signal(SIGTSTP,SIG_DFL);
}

int main()
{
	signal(SIGINT,shandler1);
	signal(SIGQUIT,shandler2);
	signal(SIGTSTP,shandler3);
	while(1)
	{
		printf("Infinite loop .......\n");
		sleep(2);
	}
	return 0;
}
