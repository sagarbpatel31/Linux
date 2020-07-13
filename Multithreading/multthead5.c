#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

int c;
void *fun(void *arg)
{
	printf("Number: %d\n",*(int *)arg);
	while(1)
	{
		c++;
		printf("In thread 1..\n");
		sleep(1);
		if(c==10)
		{
			break;
		}
	}	
	pthread_exit(&c);
	return NULL;
}

int main()
{
	int i=10;
	int *p;
	pthread_t t;
	pthread_create(&t,NULL,fun,&i);
	printf("In main thread...\n");

	pthread_join(t,(void**)&p);
	
	printf("From thread, value = %d\n",*p);
	return 0;
}
