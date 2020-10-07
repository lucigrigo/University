#include <stdio.h>

int main()
{
	printf("char: %d\nshort: %d\nunsigned: %d\nint: %d\nlong: %d\nfloat: %d\ndouble: %d\nlong double: %d\n",
	sizeof(char),sizeof(short), sizeof(unsigned),sizeof(int),  sizeof(long),
	sizeof(float), sizeof(double), sizeof(long double));
	return 0;
}
