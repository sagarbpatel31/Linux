#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

void *fun1(void *arg)
{
	while(1)
	{
		printf("In thread1...\n");
		sleep(1);
	}
}
void *fun2(void *arg)
{
        while(1)
        {
                printf("In thread2...\n");
                sleep(1);
        }
}

int main()
{
	pthread_t t1,t2;
	pthread_create(&t1,NULL,fun1,NULL);
	pthread_create(&t2,NULL,fun2,NULL);
	while(1)
	{
		printf("IN main thread......\n");	
		sleep(1);
	}
}
