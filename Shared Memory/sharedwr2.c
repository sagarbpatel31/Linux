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

	char *p,alpha='a';
	int id;
	int count=10,i;
	id=shmget(5,50,IPC_CREAT|0644);
	p=shmat(id,0,0);
	for(i=0;i<count;alpha++,i++)
	{
		*p=alpha;
		*p++;
		sleep(1);
	}
}
