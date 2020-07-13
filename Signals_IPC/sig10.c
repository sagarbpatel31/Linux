#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void shandler(int num)
{
	switch(num)
	{
		case SIGINT: 
			printf("I got SIGINT %d \n",num);
			break;
		case 3:
                        printf("I got SIGQUIT %d \n",num);
                        break;
		case 20:
                        printf("I got SIGTSTP %d \n",num);
                        break;
		case 8:
                        printf("I got SIGFPE %d \n",num);
                        break;
		case 9:
                        printf("I got SIGKILL %d \n",num);
                        break;
		case 19:
                        printf("I got SIGSTOP %d \n",num);
                        break;
	
	}
}

int main()
{
	signal(SIGINT,shandler);
	signal(SIGQUIT,shandler);
	signal(SIGTSTP,shandler);
	signal(SIGKILL,shandler);
	signal(SIGFPE,shandler);
	signal(SIGSTOP,shandler);
	
	while(1)
	{
		printf("Infinite loop .......\n");
		sleep(2);
	}
	return 0;
}
