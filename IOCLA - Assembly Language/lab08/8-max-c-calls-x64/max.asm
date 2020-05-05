section .text

global get_max

get_max:
	
	mov rbx, rdi
	mov rcx, rsi
	xor rax, rax

compare:
	cmp eax, [rbx+rcx*4-4]
	jge check_end
	mov eax, [rbx+rcx*4-4]
check_end:
	loopnz compare

	leave
	ret
