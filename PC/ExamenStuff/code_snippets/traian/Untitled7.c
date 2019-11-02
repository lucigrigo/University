#include <stdio.h>

int a=5, b=6;
int f1();
int suma()
{
	return a+b;
}
int main()
{
	f1();
	printf("%d",suma());
    return 0;
}
