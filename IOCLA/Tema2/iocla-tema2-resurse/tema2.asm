%include "include/io.inc"

extern atoi
extern printf
extern exit
extern putchar

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
	cmp eax, [ebp + 4 * 4 + 4 * 6]
	; cmp eax, [ebp + 4 * 4 + 4 * 2]
	je start_verif_sequence_task1
	xor eax, ebx
	inc ebx
	jmp iter_bruteforce_task1

start_verif_sequence_task1:
	pop ecx
	pop edx

	mov ecx, [edi + edx + 4]
	xor ecx, ebx
	cmp ecx, [ebp + 4 * 4 + 4 * 5]
	jne no_match_bruteforce_task1
	; PRINT_DEC 4, ebx
	; PRINT_
	; NEWLINE
	mov ecx, [edi + edx + 8]
	xor ecx, ebx
	cmp ecx, [ebp + 4 * 4 + 4 * 4]
	jne no_match_bruteforce_task1
	;PRINT_DEC 4, ebx
	;NEWLINE
	;PRINT_UDEC 4, [ebp + 4 * 4 + 4 * 0]
	;NEWLINE
	;PRINT_STRING "aici"
	mov ecx, [edi + edx + 12]
	xor ecx, ebx
	cmp ecx, [ebp + 4 * 4 + 4 * 3]
	jne no_match_bruteforce_task1
	mov ecx, [edi + edx + 16]
	xor ecx, ebx
	cmp ecx, [ebp + 4 * 4 + 4 * 2]
	jne no_match_bruteforce_task1
	mov ecx, [edi + edx + 20]
	xor ecx, ebx
	cmp ecx, [ebp + 4 * 4 + 4 * 1]
	jne no_match_bruteforce_task1
	mov ecx, [edi + edx + 24]
	xor ecx, ebx
	cmp ecx, [ebp + 4 * 4 + 4 * 0]
	jne no_match_bruteforce_task1

	; mov ecx, [edi + edx + 4]
	; xor ecx, ebx
	; cmp ecx, [ebp + 4 * 4 + 4 * 1]
	; jne no_match_bruteforce_task1
	; mov ecx, [edi + edx + 8]
	; xor ecx, ebx
	; cmp ecx, [ebp + 4 * 4 + 4 * 0]
	; jne no_match_bruteforce_task1

; PRINT_STRING
match_bruteforce_task:
	mov [ebp + 12], ebx

	push eax
	push ebx
	push edx

	xor edx, edx
	mov eax, esi
	mov ebx, 4
	div ebx
	xor edx, edx
	mov ebx, [img_width]
	div ebx
	mov [ebp + 8], eax

	pop edx
	pop ebx
	pop eax

no_match_bruteforce_task1:
	push edx
	push ecx
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
		push 0
		push 0
    mov edi, [img]
; start_iter:
		xor ecx, ecx

search_lines_task1:
		;xor ecx, ecx
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


search_single_line_task1:
		cmp ebx, [img_width]
		je search_lines_task1
		mov eax, ebx
		mov edx, 4
		mul dx
		add eax, esi
		; PRINT_DEC 4, eax
		; NEWLINE
		cmp byte [edi + eax], 0x00
		;xor ebx, ebx
		je search_lines_task1
		call bruteforce_task1
		inc ebx
		jmp search_single_line_task1

end_task1:
		pop eax
		pop ebx
		cmp eax, 0
		je done
		cmp ebx, 0
		je done

		mov esi, eax
		mov edx, [img_width]
		mul edx
		mov edx, 4
		mul edx
		; in eax avem acum offset-ul liniei pe care este pus mesajul
		xor ecx, ecx
		add eax, edi
		mov edi, eax

print_decrypted_message_task1: ; afisam mesajul decriptat
		mov eax, [edi + ecx * 4]
		xor eax, ebx
		push ecx
		push eax
		call putchar
		pop eax
		pop ecx
		inc ecx
		cmp eax, 46 ; ne oprim cand ajungem la '.'
		jne print_decrypted_message_task1
		NEWLINE

		PRINT_DEC 4, ebx ; cheia
		NEWLINE

		PRINT_DEC 4, esi ; linia
		NEWLINE
    jmp done

solve_task2:
		;jmp solve_task1
    PRINT_STRING "HEI"
		NEWLINE
    jmp done
		PRINT_DEC 4, esi
		NEWLINE
		PRINT_DEC 4, ebx
		NEWLINE

solve_task3:


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
