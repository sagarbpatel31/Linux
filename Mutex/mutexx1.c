#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

void *fun1(void *arg)
{
	char ch;
	for(ch = 'a';ch<='z';ch++)
	{
		pthread_mutex_lock(&m1);
		printf("%c\n",ch);
		sleep(1);
		pthread_mutex_unlock(&m);
	}	
}	
void *fun2(void *arg)
{
        int i;
        for(i= 1;i<=26;i++)
        {
                pthread_mutex_lock(&m2);
                printf("%d\n",i);
                sleep(1);
                pthread_mutex_unlock(&m1);
        }       
}  
int main()
{
	pthread_t t[2];
	char ch;
	pthread_mutex_lock(&m1);
	pthread_mutex_lock(&m2);
	pthread_create(&t[1],NULL,fun1,NULL);
	pthread_create(&t[2],NULL,fun2,NULL);
	for(ch='A';ch<='Z';ch++)
	{
		pthread_mutex_lock(&m);
		printf("%c\n",ch);
		sleep(1);
		pthread_mutex_unlock(&m2);
	}
	return 0;
} 
