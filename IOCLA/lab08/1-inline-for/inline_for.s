	.file	"inline_for.c"
	.intel_syntax noprefix
	.section	.rodata
.LC0:
	.string	"sum(%u): %u\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	lea	ecx, [esp+4]
	.cfi_def_cfa 1, 0
	and	esp, -16
	push	DWORD PTR [ecx-4]
	push	ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	mov	ebp, esp
	push	ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	sub	esp, 20
	mov	DWORD PTR [ebp-16], 100
	mov	DWORD PTR [ebp-12], 0
	mov	edx, DWORD PTR [ebp-16]
#APP
# 14 "inline_for.c" 1
	xor eax, eax
	mov ecx, edx
add_to_sum:
	add eax, ecx
	loopnz add_to_sum
	mov edx, eax
	
# 0 "" 2
#NO_APP
	mov	DWORD PTR [ebp-12], edx
	sub	esp, 4
	push	DWORD PTR [ebp-12]
	push	DWORD PTR [ebp-16]
	push	OFFSET FLAT:.LC0
	call	printf
	add	esp, 16
	mov	eax, 0
	mov	ecx, DWORD PTR [ebp-4]
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	lea	esp, [ecx-4]
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
