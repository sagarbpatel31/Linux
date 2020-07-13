#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	int i=alarm(15);
	printf("i contains %d\n",i);
	sleep(23);
	int j=alarm(5);
	printf("After alarm...j = %d \n",j);
	sleep(20);
	exit(0);
}
