extern printf
global main

section .data
    str: db "Clock ticks: %d", 10, 13

section .text
main:
    push ebp
    mov ebp, esp

    mov ecx, 1000
    xor eax, eax

    ; TODO:
    ; 1. call rdtsc

	rdtsc

    ; 2. save the the value from eax to another register

	mov ebx, eax

    ; 3. implement the loop using loop, then a jump instruction

	start_loop:
		loop start_loop

	mov ecx, 1000
	jmp_loop:
		cmp ecx, 0
		jne next_label
		dec ecx
		jmp jmp_loop

    ; 4. call rdtsc again
	next_label:
		rdtsc
    ; 5. subtract from eax the former value of eax
	sub eax, ebx
	;mov eax, ebx
    push eax
    push str
    call printf
    add esp, 8

    mov esp, ebp
    pop ebp
    ret
