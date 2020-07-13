#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>

pthread_mutex_t m,m1;
FILE *fp;
void *fun(void *arg)
{
	char ch;
	for(ch = 'a';ch<='z';ch++)
	{
		pthread_mutex_lock(&m1);
		fprintf(fp,"%c ",ch);
		pthread_mutex_unlock(&m);
	}	
}	
int main()
{
	pthread_t t;
	pthread_mutex_init(&m,NULL);
	pthread_mutex_init(&m1,NULL);
	fp=fopen("data","w");
	char ch;
	pthread_mutex_lock(&m1);
	pthread_create(&t,NULL,fun,NULL);
	for(ch='A';ch<='Z';ch++)
	{
		pthread_mutex_lock(&m);
		fprintf(fp,"%c ",ch);
		pthread_mutex_unlock(&m1);
	}
	return 0;
} 
