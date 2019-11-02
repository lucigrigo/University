#include <stdio.h>

int main()
{
	unsigned char a=0, mask=0xff;

	printf("a&mask:%d\na|mask:%d\na^mask:%d\na<<1:%d\na>>1:%d\nmask<<1:%d\nmask>>1:%d\n",a&mask,a|mask,a^mask,a<<1,a>>1,mask<<1, mask>>1);
	return 0;

}	
