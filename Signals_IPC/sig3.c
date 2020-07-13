#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	printf("After 3 seconds, it will stop....\n");
	sleep(3);
	kill(getpid(),1);
	printf("Not printed....\n");
	return 0;
}
