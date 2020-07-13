#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
struct msgbuf
{
	long m_type;
	char msg_txt[10];
};
void main()
{
	struct msgbuf v;
	int id;
	id = msgget(9,IPC_CREAT|0644);
	printf("id = %d\n",id);
	printf("Enter the data.....\n");
	scanf("%s",v.msg_txt);
	v.m_type=2;
	msgsnd(id,v.msg_txt,strlen(v.msg_txt)+1,0);
	perror("msgsnd");
}
