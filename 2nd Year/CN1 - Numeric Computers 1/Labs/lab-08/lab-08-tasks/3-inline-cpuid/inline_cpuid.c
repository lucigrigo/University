#include <stdio.h>

int main(void)
{
	char cpuid_str[13];

	__asm__ (""
	/* TODO: Make cpuid call and copy string in cpuid_str.
	 * eax needs to be 0
	 * After cpuid call string is placed in (ebx, edx, ecx).
	 */
		"xor eax, eax\n"
		"cpuid\n"
		"mov eax, %0\n"
		"mov [eax + 8], ecx\n"
		"mov [eax + 0], ebx\n"
		"mov [eax + 4], edx\n"
		:
		: "r" (cpuid_str)
		: "eax", "ebx", "ecx", "edx"
	);

	cpuid_str[12] = '\0';

	printf("CPUID string: %s\n", cpuid_str);

	return 0;
}
