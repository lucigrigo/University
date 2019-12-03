%include "include/io.inc"

extern atoi
extern printf
extern exit

; Functions to read/free/print the image.
; The image is passed in argv[1].
extern read_image
extern free_image
; void print_image(int* image, int width, int height);
extern print_image

; Get image's width and height.
; Store them in img_[width, height] variables.
extern get_image_width
extern get_image_height

section .data
	use_str db "Use with ./tema2 <task_num> [opt_arg1] [opt_arg2]", 10, 0

section .bss
    task:       resd 1
    img:        resd 1
    img_width:  resd 1
    img_height: resd 1


section .text

bruteforce_task1:
	push ebp
	mov ebp,esp
	push ebx
	push ecx
	mov ecx, [edi + eax]
	push eax
	push edx
	;PRINT_DEC 4, ecx
	;NEWLINE

	;mov ecx, 114
	xor ebx, ebx
	mov eax, ecx

iter_bruteforce_task1:
	cmp ebx, 255
	je end_iter_bruteforce_task1
	xor eax, ebx
	cmp eax, 114
	je start_verif_sequence_task1
	xor eax, ebx
	inc ebx
	jmp iter_bruteforce_task1

start_verif_sequence_task1:
	pop edx
	pop ecx

	PRINT_DEC 4, [ebp + 16] ; 'e'
	NEWLINE

match_bruteforce_task:

	;push 0
	;call exit

no_match_bruteforce_task1:
	push ecx
	push edx
	xor eax, ebx
	inc ebx
	jmp iter_bruteforce_task1

end_iter_bruteforce_task1:
	pop edx
	pop eax
	pop ecx
	pop ebx
	pop ebp
	ret

global main
main:
    ; Prologue
    ; Do not modify!
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]
    cmp eax, 1
    jne not_zero_param

    push use_str
    call printf
    add esp, 4

    push -1
    call exit

not_zero_param:
    ; We read the image. You can thank us later! :)
    ; You have it stored at img variable's address.
    mov eax, [ebp + 12]
    push DWORD[eax + 4]
    call read_image
    add esp, 4
    mov [img], eax

    ; We saved the image's dimensions in the variables below.
    call get_image_width
    mov [img_width], eax

    call get_image_height
    mov [img_height], eax

    ; Let's get the task number. It will be stored at task variable's address.
    mov eax, [ebp + 12]
    push DWORD[eax + 8]
    call atoi
    add esp, 4
    mov [task], eax

    ; There you go! Have fun! :D
    mov eax, [task]
    cmp eax, 1
    je solve_task1
    cmp eax, 2
    je solve_task2
    cmp eax, 3
    je solve_task3
    cmp eax, 4
    je solve_task4
    cmp eax, 5
    je solve_task5
    cmp eax, 6
    je solve_task6
    jmp done

solve_task1:
		push 114
		push 101
		push 118
		push 105
		push 101
		push 110
		push 116
    mov edi, [img]
		xor ecx, ecx

search_lines_task1:
		cmp ecx, [img_height]
		je end_task1
		mov eax, ecx
		mov edx, 4
		mul dx
		mov edx, [img_width]
		mul dx
		inc ecx
		mov esi, eax
		xor ebx, ebx
		;NEWLINE

search_single_line_task1:
		cmp ebx, [img_width]
		je search_lines_task1
		mov eax, ebx
		mov edx, 4
		mul dx
		add eax, esi
		;PRINT_DEC 4, [edi + eax]
	 	;NEWLINE
		;push eax
		;push
		;je find
		cmp byte [edi + eax], 0x00
		je end_task1
		;push BYTE[edi + eax]
		call bruteforce_task1
		;sub esp, 4
		inc ebx
		jmp search_single_line_task1

end_task1:
		; todo store info in eax for task2
		;PRINT_STRING "aici la final"
		;NEWLINE
    jmp done

solve_task2:
    ; TODO Task2
    jmp done
solve_task3:
    ; TODO Task3
    jmp done
solve_task4:
    ; TODO Task4
    jmp done
solve_task5:
    ; TODO Task5
    jmp done
solve_task6:
    ; TODO Task6
    jmp done

    ; Free the memory allocated for the image.
done:
    push DWORD[img]
    call free_image
    add esp, 4

    ; Epilogue
    ; Do not modify!
    xor eax, eax
    leave
    ret
