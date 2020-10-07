#include <stdio.h>

int main()
{
	int x=5, y=2, z=-3;
	printf("x/y (intreg)=%d, x%%y=%d, x/z(intreg)=%d, x%%z=%d\n", x/y,x%y,-x/-z,-x%-z);
	printf("x/y=%f, x/z=%f\n", x*1.0/y,x*1.0/z); 
	return 0;	
}
