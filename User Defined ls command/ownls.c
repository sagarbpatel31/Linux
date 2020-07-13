#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	DIR *dp;
	struct dirent *dirp;

	if(argc != 2)
	{
		printf("Please provide the directory to the list out.....\n");
		exit(1);
	}
	if((dp=opendir(argv[1]))==NULL)
	{
		printf("Cannot open directory error = %s\n",strerror(errno));
		exit(1);
	}
	while((dirp = readdir(dp))!=NULL)
		printf("%s\n",dirp->d_name);
	closedir(dp);
	exit(0);
}
