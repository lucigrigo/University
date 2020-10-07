#include <stdio.h>

int main()
{
	char c;
	int exit=0,print=1;
	while(1)
	{
		if(print)
		{
			printf("Alegeti una din urmatoarele optiuni:\n");
			printf("S - Start program\n");
			printf("O - Optiuni program\n");
			printf("X - Iesire program\n");
		}
		c=getchar();
		switch(c)
		{
			case 's':
			case 'S': printf("s-a executat programul\n"); print=1;
		        case 'o':
			case 'O': printf("nici o optiune disponibila\n");print=1;
		        case 'x':
			case 'X': exit=1; break;
			default:print=0;
			
		}
		if(exit==1)
			break;

	}
	return 0;
}
