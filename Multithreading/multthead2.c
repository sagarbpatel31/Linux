#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

pthread_t t[2];
void *fun(void *arg)
{
	pthread_t id = pthread_self();
	if(pthread_equal(id,t[0]))
	{
		printf("In first thread.....\n");
	}
	else if(pthread_equal(id,t[1]))
	{
		printf("In second thread.....\n");
	}
	sleep(2);
	return NULL;

}

int main()
{
	int i=0;
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
	sleep(5);
	return 0;
}
