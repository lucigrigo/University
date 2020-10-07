#include <stdio.h>
#include <stdlib.h>
/* verifica daca al 4-lea bit dintr-un octet este 0 sau 1*/
int main()
{
	//mask va fi 00001000
	unsigned char mask=8, randomNumber;
	srand(time(NULL));
	randomNumber=rand()%255;
	printf("mask=%d, randomNumber=%d, al 4-lea bit este %s (%d)\n",mask,randomNumber,((mask&randomNumber)==mask)?"1":"0",mask&randomNumber);
	return 0;

}
