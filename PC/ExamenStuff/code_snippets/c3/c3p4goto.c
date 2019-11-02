#include<stdio.h>

int main()
{
	int i=0;
eticheta:
	if(i%3!=0)
		printf("i=%d\n",i);
	i++;
	if(i<10)
		goto eticheta;
	return 0;

}
