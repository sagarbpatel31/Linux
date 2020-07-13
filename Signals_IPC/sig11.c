#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void shandler(int num)
{
	static int count=0;
	count++;
	printf("Don't do it again....\n");
	if(count>5)
	{
		printf("Don't do it again or else it will die..\n");	
		signal(SIGINT,SIG_DFL);
	}

}

int main()
{
	signal(SIGINT,shandler);
	
	while(1)
	{
		printf("Infinite loop .......\n");
		sleep(2);
	}
	return 0;
}
