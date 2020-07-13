#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	while(1)
	{
		printf("In Infinite loop Press Ctrl + C to exit...\n");
		sleep(2);	
	}
	return 0;
}
