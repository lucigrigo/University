global computeLength1
global computeLength2

section .text
computeLength1:
	push ebp
	mov ebp, esp
	xor eax, eax
	xor ebx, ebx
	mov edx, dword [ebp + 8]
;TODO: Implement byte count using a software loop
count:
	mov bl, byte [edx]
	test bl, bl
	je out
	inc eax
	inc edx
	jmp count
out:
	mov esp, ebp
	pop ebp
	ret

computeLength2:
	push ebp
	mov ebp, esp
;TODO: Implement byte count using a hardware loop
	xor ecx, ecx
	not ecx
	mov edi, dword [ebp + 8]
	sub al, al
	cld
	repne scasb
	not ecx
	dec ecx

	mov eax, ecx

	mov esp, ebp
	pop ebp
	ret
