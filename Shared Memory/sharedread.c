#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>


int main()
{

	char *read;
	int id,i;
	id=shmget(5,50,IPC_CREAT|0644);
	read=shmat(id,0,0);
	for(i=0;i<=20;read++,i++)
	{
		printf("%c ",*read);
		sleep(1);
	}
}
