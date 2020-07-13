#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void shandler1(int num)
{
	printf("In handler 1....\n");
}
void shandler2(int num)
{
        printf("In handler 2.....\n");
}

int main()
{
	void (*old) (int);
	signal(SIGHUP,shandler1);
	sleep(2);
	raise(SIGHUP);
	old=signal(SIGHUP,shandler2);
	sleep(2);
	raise(SIGHUP);
	signal(SIGHUP,old);
	sleep(2);
	raise(SIGHUP);
	signal(SIGHUP,SIG_DFL);
	sleep(2);
	raise(SIGHUP);
	sleep(4);
	return 0;
}
