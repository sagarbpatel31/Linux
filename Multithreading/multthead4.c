#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

pthread_t t[2];
int r1,r2;
void *fun(void *arg)
{
	pthread_t id = pthread_self();
	sleep(1);
	if(pthread_equal(id,t[0]))
	{
		printf("In first thread.....\n");
		r1=10;
		pthread_exit(&r1);
	}
	else if(pthread_equal(id,t[1]))
	{
		printf("In second thread.....\n");
		r2=20;
		pthread_exit(&r2);
	}
	return NULL;
}

int main()
{
	int i=0;
	int *p[2];
	int err;
	while(i<2)
	{
		err=pthread_create(&t[i],NULL,fun,NULL);
		if(err!=0)
		{
			printf("Thread not created.....\n");
		}
		else
		{
			printf("In main thread.. %d...\n",i);
		}
		i++;
	}	
	pthread_join(t[0],(void**)&p[0]);
	pthread_join(t[1],(void**)&p[1]);
	printf("From thread 1, value = %d\n",*p[0]);
	printf("From thread 2, value = %d\n",*p[1]);
	return 0;
}
