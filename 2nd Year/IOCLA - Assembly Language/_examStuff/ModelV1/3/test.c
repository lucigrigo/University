#include <stdio.h>

void direct(const char *s, unsigned int perturb);
size_t obvious(unsigned int a, unsigned int b);
void crypto(const unsigned char *in, unsigned char *out, size_t len, const unsigned char *key, size_t klen);

int main(void)
{
	unsigned char in[128] = "no country for old men";
	unsigned char out[128];
	unsigned char k[16] = "sibling1";

	direct("bad.", 800);
	printf("%d\n", obvious(179, 1));

	int i;
	for(i = 0; i < 24; i++){
		in[i] = k[i % 16] ^ in[i];
	}
	
	crypto(in, out, 128, k, 16);
	printf("%s", out);

	return 0;
}
