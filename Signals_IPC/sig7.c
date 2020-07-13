#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	struct sigaction s;
	s.sa_handler=SIG_IGN;
	s.sa_flags=0;	
	sigemptyset(&s.sa_mask);
	sigaction(SIGINT,&s,NULL);
	sigaction(SIGFPE,&s,NULL);

	while(1)
	{
		printf("Infinite loop .......\n");
		printf("Can't kill by <2> or <8> signal....\n");
		sleep(3);
	}
	return 0;
}
