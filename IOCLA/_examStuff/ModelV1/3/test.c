#include <stdio.h>

void direct(const char *s, unsigned int perturb);
size_t obvious(unsigned int a, unsigned int b);
void crypto(const unsigned char *in, unsigned char *out, size_t len, const unsigned char *key, size_t klen);

int main(void)
{
	unsigned char in[128];
	unsigned char out[128];
	unsigned char k[16];

	direct("ana", 100);
	obvious(0, 0);
	crypto(in, out, 128, k, 16);

	return 0;
}
