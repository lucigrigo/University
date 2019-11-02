#include <stdio.h>
#include<stdlib.h>

int main()
{
	int haveEggs;
	srand(time(NULL));
	haveEggs=rand()%2;
	if(haveEggs!=0)
		printf("i bought  12 gallons of milk\n");
 	else
		printf("i bought 1 gallon of milk\n");
	return 0;

}

