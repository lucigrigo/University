#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#define DIE(assertion, call_description)    \
	do {							    	\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",	\
					__FILE__, __LINE__);    \
			perror(call_description);		\
			exit(errno);					\
		}							        \
	} while (0)

/*
 * hexstr_to_bytes - converts a hex string to a byte array
 *  @src : source hexstring buffer
 *  @dst : destination byte array buffer
 *  @n   : number of bytes to interpret (src must be 2*n)
 */
void hexstr_to_bytes(char *src, unsigned char *dst, size_t n)
{
    for (size_t i=0; i<n; ++i)
        sscanf(&src[2*i], "%2hhx", &dst[i]);
}

int main(size_t argc, char *argv[])
{
    /* 16 byte salt must be provided as 32 byte hexstr */
    DIE(argc != 2, "./oracle hexlify(IV)");
    DIE(strlen(argv[1]) != 32, "16 byte IV => 32 byte hexstr");

    /* definitions */
    EVP_CIPHER_CTX *ctx;
    unsigned char key[32] = {
        0xa5, 0xca, 0x80, 0xf2, 0x1e, 0x26, 0x19, 0x57,
        0x2b, 0xd8, 0x62, 0x87, 0x21, 0x9c, 0x21, 0x30,
        0x0a, 0x5f, 0x89, 0xfb, 0x61, 0x9e, 0x53, 0x3e,
        0xa4, 0x38, 0x02, 0xf6, 0x19, 0x90, 0xf7, 0xa3 };
    unsigned char iv[16] = { [0 ... 15] = 0x00 };
    unsigned char enc[32] = { 
        0x19, 0x50, 0x4e, 0x70, 0x73, 0x11, 0x08, 0x75,
        0x06, 0xb8, 0x60, 0xb9, 0xfa, 0x6d, 0xdc, 0x2f,
        0x5f, 0x61, 0x41, 0x62, 0x61, 0x3f, 0xfe, 0x23,
        0xd9, 0xb7, 0xa0, 0xe8, 0xa6, 0xeb, 0x58, 0xd7 };
    unsigned char dec[32] = { [0 ... 31] = 0x00 };
    int len, ans;


    /* obtain the IV from the argv[1] hexstring */
    hexstr_to_bytes(argv[1], iv, sizeof(iv));

    /* decrypt */
    ctx = EVP_CIPHER_CTX_new();
    DIE(!ctx, "Error creating cipher context");

    ans = EVP_DecryptInit(ctx, EVP_aes_256_cbc(), key, iv);
    DIE(ans != 1, "DecryptInit failed");

    ans = EVP_DecryptUpdate(ctx, dec, &len, enc, 32);
    DIE(ans != 1, "DecryptUpdate failed");

    ans = EVP_DecryptFinal(ctx, dec + len, &len);
    DIE(ans != 1, "DecryptFinal failed");

    EVP_CIPHER_CTX_free(ctx);

    /* display result */
    dec[16] = 0x00;
    printf("Decrypted text is: %s\n", dec);

    return 0;
}