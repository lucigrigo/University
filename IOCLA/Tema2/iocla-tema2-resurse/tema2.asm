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
		; push ecx
		; push eax
		; call putchar
		; pop eax
		; pop ecx
		PRINT_CHAR eax
		inc ecx
		cmp eax, 46 ; ne oprim cand ajungem la '.'
		jne print_decrypted_message_task1
		NEWLINE

		PRINT_DEC 4, ebx ; cheia
		NEWLINE

		PRINT_DEC 4, esi ; linia
		NEWLINE

		; mov ah, bl
		; mov	al, byte[esi]
    jmp done

solve_task2:
		; jmp solve_task1
    ; PRINT_STRING "HEI"
		; NEWLINE
		;
		; PRINT_DEC 1, al
		; NEWLINE
		; 'C'est un proverbe francais.'
		; new_key = floor((2 * old_key + 3) / 5) - 4
		jmp done

solve_task3:
		; citirea argumentelor
		; mov eax, [ebp + 12]
		; mov ebx, [eax]
		; mov eax, [ebx]
		; PRINT_STRING [ebx + 29] ; inceputul argumentelor
		; NEWLINE


		; cautam offsetul care se afla dupa spatiu
		mov eax, [ebp + 12]
		mov edi, [eax] ; in edi avem argumentele
		mov ecx, 28

search_offset_value_task3:
		inc ecx
	;	PRINT_STRING [edi + eax]
	;	NEWLINE
		cmp byte[edi + ecx], 0x00
		jne search_offset_value_task3
	 	; mov eax, [edi + ecx + 1]
		; PRINT_STRING [edi + eax + 1]
		; NEWLINE

		mov ebx, ecx
		mov eax, [ebp + 12]
		; mov eax, [eax]
		;mov ecx, eax
		push DWORD[eax + 16]
		call atoi
		add esp, 4
		; PRINT_STRING [eax + ecx]
		; PRINT_STRING [edi + ecx + 1]
		;mov ebx, eax
		; PRINT_DEC 4, eax
		; NEWLINE

		; PRINT_DEC 4, ebx
		; NEWLINE
		; jmp start_writing_message_task3

		; push DWORD[0x00]
		push 0x00
		mov ecx, ebx
		dec ecx
start_crypting_task3:
		; PRINT_STRING [edi + ecx]
		; NEWLINE
		cmp ecx, 28
		je start_writing_message_task3
		cmp byte[edi + ecx], "A"
		je crypt_A
		cmp byte[edi + ecx], "B"
		je crypt_B
		cmp byte[edi + ecx], "C"
		je crypt_C
		cmp byte[edi + ecx], "D"
		je crypt_D
		cmp byte[edi + ecx], "E"
		je crypt_E
		cmp byte[edi + ecx], "F"
		je crypt_F
		cmp byte[edi + ecx], "G"
		je crypt_G
		cmp byte[edi + ecx], "H"
		je crypt_H
		cmp byte[edi + ecx], "I"
		je crypt_I
		cmp byte[edi + ecx], "J"
		je crypt_J
		cmp byte[edi + ecx], "K"
		je crypt_K
		cmp byte[edi + ecx], "L"
		je crypt_L
		cmp byte[edi + ecx], "M"
		je crypt_M
		cmp byte[edi + ecx], "N"
		je crypt_N
		cmp byte[edi + ecx], "O"
		je crypt_O
		cmp byte[edi + ecx], "P"
		je crypt_P
		cmp byte[edi + ecx], "Q"
		je crypt_Q
		cmp byte[edi + ecx], "R"
		je crypt_R
		cmp byte[edi + ecx], "S"
		je crypt_S
		cmp byte[edi + ecx], "T"
		je crypt_T
		cmp byte[edi + ecx], "U"
		je crypt_U
		cmp byte[edi + ecx], "V"
		je crypt_V
		cmp byte[edi + ecx], "W"
		je crypt_W
		cmp byte[edi + ecx], "X"
		je crypt_X
		cmp byte[edi + ecx], "Y"
		je crypt_Y
		cmp byte[edi + ecx], "Z"
		je crypt_Z
		cmp byte[edi + ecx], ","
		je crypt_comma
		jmp start_crypting_task3

crypt_A:
push " "
push "-"
push "."
dec ecx
jmp start_crypting_task3

crypt_B:
push " "
push "."
push "."
push "."
push "-"
dec ecx
jmp start_crypting_task3

crypt_C:
push " "
push "."
push "-"
push "."
push "-"
dec ecx
jmp start_crypting_task3

crypt_D:
push " "
push "."
push "."
push "-"
dec ecx
jmp start_crypting_task3

crypt_E:
push " "
push "."
dec ecx
jmp start_crypting_task3

crypt_F:
push " "
push "."
push "-"
push "."
push "."
dec ecx
jmp start_crypting_task3

crypt_G:
push " "
push "."
push "-"
push "-"
dec ecx
jmp start_crypting_task3

crypt_H:
push " "
push "."
push "."
push "."
push "."
dec ecx
jmp start_crypting_task3

crypt_I:
push " "
push "."
push "."
dec ecx
jmp start_crypting_task3

crypt_J:
push " "
push "-"
push "-"
push "-"
push "."
dec ecx
jmp start_crypting_task3

crypt_K:
push " "
push "-"
push "."
push "-"
dec ecx
jmp start_crypting_task3

crypt_L:
push " "
push "."
push "."
push "-"
push "."
dec ecx
jmp start_crypting_task3

crypt_M:
push " "
push "-"
push "-"
dec ecx
jmp start_crypting_task3

crypt_N:
push " "
push "."
push "-"
dec ecx
jmp start_crypting_task3

crypt_O:
push " "
push "-"
push "-"
push "-"
dec ecx
jmp start_crypting_task3

crypt_P:
push " "
push "."
push "-"
push "-"
push "."
dec ecx
jmp start_crypting_task3

crypt_Q:
push " "
push "-"
push "."
push "-"
push "-"
dec ecx
jmp start_crypting_task3

crypt_R:
push " "
push "."
push "-"
push "."
dec ecx
jmp start_crypting_task3

crypt_S:
push " "
push "."
push "."
push "."
dec ecx
jmp start_crypting_task3

crypt_T:
push " "
push "-"
dec ecx
jmp start_crypting_task3

crypt_U:
push " "
push "-"
push "."
push "."
dec ecx
jmp start_crypting_task3

crypt_V:
push " "
push "-"
push "."
push "."
push "."
dec ecx
jmp start_crypting_task3

crypt_W:
push " "
push "-"
push "-"
push "."
dec ecx
jmp start_crypting_task3

crypt_X:
push " "
push "-"
push "."
push "."
push "-"
dec ecx
jmp start_crypting_task3

crypt_Y:
push " "
push "-"
push "-"
push "."
push "-"
dec ecx
jmp start_crypting_task3

crypt_Z:
		push " "
		push "."
		push "."
		push "-"
		push "-"
		dec ecx
		jmp start_crypting_task3

crypt_comma:
push " "
push "-"
push "-"
push "."
push "."
push "-"
push "-"
dec ecx
jmp start_crypting_task3

start_writing_message_task3:
		mov edi, [img]
		mov ebx, 4
		mul ebx
		; mov edi, [edi]
		; mov edi, [ebx]
		; mov bl, byte[esp]
		; sub esp, 1
iteration_writing_message_task3:
		pop ebx
		cmp ebx, 0
		; PRINT_DEC 4, ebx
		; PRINT_DEC 4, eax
		; PRINT_STRING [ebx]
		; NEWLINE
		; mov ebx, [ebx]
		; mov edx, [ebx]
		je end_message_task3
		mov	byte[edi + eax], bl
		add eax, 4
		jmp iteration_writing_message_task3

		; mov esp, ebp
end_message_task3:
		sub eax, 4
		mov byte[edi + eax], 0

		push DWORD[img_height]
		push DWORD[img_width]
		push DWORD[img]
		call print_image
		add esp, 12


		; parcurgem textul de la final si il codificam

		; punem codificarea pe stiva

		; punem in imagine valorile de pe stiva

    jmp done

solve_task4:
    ; TODO Task4
    jmp done
solve_task5:
    ; TODO Task5
    jmp done
solve_task6:


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
