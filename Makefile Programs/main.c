#include<stdio.h>
#include "fun.h"
int main()
{
	float a,t;
	printf("Enter the number.....\n");
	scanf("%f",&a);
	printf("The entered number is %f\n",a);
	t=square(a);
	print(t);
	return 0;
}
