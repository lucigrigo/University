section .text

global get_max

get_max:
	push ebp
	mov ebp, esp

	; save ebx in callee
	push ebx

	; [ebp+8] is array pointer
	; [ebp+12] is array length

	mov ebx, [ebp+8]
	mov ecx, [ebp+12]
	mov edi, [ebp+16]
	xor eax, eax
	xor edx, edx

compare:
	inc edx
	cmp eax, [ebx+ecx*4-4]
	jge check_end
	mov [edi], edx
	mov eax, [ebx+ecx*4-4]
check_end:
	loopnz compare

	pop ebx

	leave
	ret
