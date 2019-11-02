#include <stdio.h>
#include <stdlib.h>
int main()
{
	int v[10]={0};
	int *p=v,i;
	srand(time(NULL));
	printf("p=%p, v=%p\n",p,v);
	for(i=0;i<10;i++)
		v[i]=rand()%100;

	for(i=0;i<10;i++,p++)
		printf("v[i]=%i,*p=%i, v+i=%p, p=%p\n",v[i],*p,v+i,p);


	return 0;
}
