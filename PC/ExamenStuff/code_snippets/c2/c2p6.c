#include <stdio.h>
#include <stdlib.h>

int main()
{
	int play, goOut;
	srand(time(NULL));
	play=rand()%2;
	goOut=1-play;
	printf("go out=%s, play=%s, go out or play=%s\n",goOut==1?"yes":"no",
			play==1?"yes":"no",(goOut||play)==1?"yes":"no");

	return 0;

}
