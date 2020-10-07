#include <stdio.h>

#define NUM	0x12345678

int main(void)
{
	size_t n = NUM;
	size_t rot_left;
	size_t rot_right;

	__asm__ (""
	/* TODO: Use rol instruction to shift n by 8 bits left.
	 * Place result in rot_left variable.
	 */
	"mov eax, %2\n"
	"rol eax, 8\n"
	"mov %0, eax\n"
	/* TODO: Use ror instruction to shift n by 8 bits right.
	 * Place result in rot_right variable.
	 */
	"mov ebx, %2\n"
	"ror ebx, 8\n"
	"mov %1, ebx\n"
	/* TODO: Declare output variables - preceded by ':'. */
	: "=r" (rot_left),
	 "=r" (rot_right)
	/* TODO: Declare input variables - preceded by ':'. */
	: "r" (n)
	/* TODO: Declared used registers - preceded by ':'. */
	: "eax", "ebx"
	);

	/* NOTE: Output variables are passed by address, input variables
	 * are passed by value.
	 */

	printf("init: 0x%08x, rot_left: 0x%08x, rot_right: 0x%08x\n",
			n, rot_left, rot_right);

	return 0;
}
