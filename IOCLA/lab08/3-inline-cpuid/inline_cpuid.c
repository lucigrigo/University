#include <stdio.h>

int main(void)
{
	char cpuid_str[13];

	__asm__ (
	"xor eax, eax\n\t"
	/* TODO: Make cpuid call and copy string in cpuid_str.
	 * eax needs to be 0
	 * After cpuid call string is placed in (ebx, edx, ecx).
	 */
	"cpuid\n\t"	
	"mov eax, %0\n"
	"mov [eax], ebx\n"
	"mov [eax+4], ecx\n"
	"mov [eax+8], edx\n"
	: 
	: "r" (cpuid_str)
	: "eax", "ebx", "ecx", "edx" );

	cpuid_str[12] = '\0';

	printf("CPUID string: %s\n", cpuid_str);

	return 0;
}
