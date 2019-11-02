#include <stdio.h>

int main()
{
	int x=5;
	printf("x= %d; adresa lui x=%p\n",x,&x);
	x=x+1;
	printf("x= %d; adresa lui x=%p\n",x,&x);
	
	printf("x=5: %d x==0:%d  x =0:%d x==0:%d\n",x=5,x==0,x=0,x==0);
	return 0;	


}

