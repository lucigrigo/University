#include <stdio.h>
#include <string.h>

int main() {

	char str[] = "CevaString";
	char src[] = "eda";

	int idxStr = 0;
	int idxSrc = 0;


start:
	idxStr = idxStr - idxSrc + 1;
	idxSrc = 0;

check:
	if(idxStr >= strlen(str))
		goto notFound;

	if(idxSrc == strlen(src))
		goto found;

	if(str[idxStr] != src[idxSrc])
		goto start;

	idxStr++;
	idxSrc++;
	goto check;

found:
	printf("A fost gasit!\n");
	goto end;

notFound:
	printf("N-a fost gasit.\n");
	goto end;

end:
	return 0;
	

}
