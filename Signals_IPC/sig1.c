#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	printf("In a running Process..\n");
	sleep(1);
	printf("Divide by zero...\n");
	sleep(1);
	int a=3,b=3;
	float ans = 20 / (a-b);
	return 0;
}
