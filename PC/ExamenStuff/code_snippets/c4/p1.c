#include<stdio.h>
int main()
{
	int *p1, x;
	printf("p1=%p, x=%d\n",p1,x);
	x=5;
	p1=&x;
	printf("p1=%p, x=%d\n",p1,x);
	return 0;

}
