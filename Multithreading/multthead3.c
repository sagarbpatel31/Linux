#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

void *fun(void *arg)
{
	printf("Number: %d\n",*(int *)arg);
	while(1)
	{
		printf("In thread 1....\n");
		sleep(1);
	}
}

int main()
{
	pthread_t t;
	int num = 10;
	pthread_create(&t,NULL,fun,&num);
	while(1)
	{
		printf("In main thread....\n");
		sleep(1);
	}
	return 0;
}
