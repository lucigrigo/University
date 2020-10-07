; Grigore Lucian-Florin
; Grupa 324CD, Anul II
; Facultatea de Automatica si Calculatoare
; Universitatea Politehnica, Bucuresti
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

section .rodata
	task2_message db "C'est un proverbe francais.", 10, 0

section .bss
    task:       resd 1
    img:        resd 1
    img_width:  resd 1
    img_height: resd 1

section .text

verif_match_task1:
		push ebp
		mov ebp, esp

		xor edx, edx
		mov edx, [edi + eax + 4]
		xor edx, ebx
		cmp edx, "e"
		jne no_match_found_task1
		xor edx, edx
		mov edx, [edi + eax + 8]
		xor edx, ebx
		cmp edx, "v"
		jne no_match_found_task1
		xor edx, edx
		mov edx, [edi + eax + 12]
		xor edx, ebx
		cmp edx, "i"
		jne no_match_found_task1
		xor edx, edx
		mov edx, [edi + eax + 16]
		xor edx, ebx
		cmp edx, "e"
		jne no_match_found_task1
		xor edx, edx
		mov edx, [edi + eax + 20]
		xor edx, ebx
		cmp edx, "n"
		jne no_match_found_task1
		xor edx, edx
		mov edx, [edi + eax + 24]
		xor edx, ebx
		cmp edx, "t"
		jne no_match_found_task1

found_match_task1:
		mov [ebp + 12], ebx
		push ebx
		mov ebx, [ebp + 8]
		mov [ebp + 16], ebx
		pop ebx

no_match_found_task1:
		leave
		ret

encrypt_message_task2:
		push ebp
		mov ebp, esp

		; mesajul pe care vrem sa il criptam este
		; "C'est un proverbe francais."
		mov ebx, eax ; in ebx vom tine minte noua cheie
		push ebx
		mov eax, ecx ; in eax vrem sa aflam offsetul de la care sa incepem
		add eax, 1 ; dorim sa incepem de pe linia urmatoare mesajului decriptat
		mov ebx, [img_width]
		mul ebx
		mov ebx, 4
		mul ebx
		pop ebx
		; PRINT_DEC 4, ecx

		; incepem scrierea mesajului
		xor ecx, ecx

write_message_task2:
		mov edx, [task2_message + ecx]
		; xor edx, ebx
		mov byte[edi + eax], dl
		cmp byte[task2_message + ecx], "."
		je done_writing_message_task2
		add ecx, 1
		add eax, 4
		jmp write_message_task2

done_writing_message_task2:
		mov byte[edi + eax + 4], 0
		xor ecx, ecx
		mov eax, [ebp + 8]

encrypt_new_image_task2:
		cmp ecx, eax
		je finished_encryption_task2
		mov edx, [edi + ecx]
		xor edx, ebx
		mov byte[edi + ecx], dl
		add ecx, 4
		jmp encrypt_new_image_task2

finished_encryption_task2:
		pop eax
		leave
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
		; in edi memoram adresa imaginii
		mov edi, [img]
		mov eax, 4
		mov ebx, [img_width]
		mul ebx
		mov ebx, [img_height]
		mul ebx
		mov esi, eax ; in esi memoram dimensiunea maxima a imaginii
		xor ebx, ebx ; in ebx vom memora cheia de decriptare curenta
		push ebx
		push ebx

key_iteration_task1:
		pop ecx
		cmp ebx, 256
		je done_task1
		xor eax, eax
		xor ecx, ecx
		push ecx

iterate_through_image_task1:
		cmp eax, esi
		je done_iteration_for_current_key_task1
		cmp ecx, [img_width]
		je new_line_task1
continue_current_line_task1:
		xor edx, edx
		mov edx, [edi + eax]
		xor edx, ebx
		cmp edx, "r"
		jne next_iter
		call verif_match_task1
next_iter:
		add eax, 4
		inc ecx
		jmp iterate_through_image_task1

done_iteration_for_current_key_task1:
		inc ebx
		jmp key_iteration_task1

new_line_task1:
		pop ecx
		inc ecx
		push ecx
		xor ecx, ecx
		jmp continue_current_line_task1

done_task1:
		pop ebx ; in ebx avem cheia cu care am decriptat mesajul
		pop ecx ; in ecx avem linia pe care am gasit mesajul
		cmp byte[task], 1
		jne verif_task2
		; afisam mesajul decriptat
		push ebx
		xor eax, eax
		mov eax, ecx
		mov esi, ecx
		mov ebx, 4
		mul ebx
		mov ebx, [img_width]
		mul ebx
		; in eax avem acum offsetul de la care incepe linia pe care am gasit mesajul
		pop ebx

continue_printing_task1:
		xor edx, edx
		mov edx, [edi + eax]
		xor edx, ebx ; aplicam XOR cu cheia gasita
		PRINT_CHAR edx ; printam caracterul creunt
		cmp edx, "." ; verificam daca am printat ultimul caracter
		je done_printing_message_task1
		add eax, 4 ; trecem la urmatorul octet
		jmp continue_printing_task1

done_printing_message_task1:
		NEWLINE
		PRINT_DEC 4, ebx
		NEWLINE
		PRINT_DEC 4, esi
		NEWLINE
    jmp done

solve_task2:
		jmp solve_task1
verif_task2:
		cmp byte[task], 2
		jne done
		push ecx
		push ecx
		; in edi memoram adresa imaginii
		mov edi, [img]
		push ebx
		xor eax, eax
		mov eax, 4
		mov ebx, [img_width]
		mul ebx
		mov ebx, [img_height]
		mul ebx
		; dorim sa aplicam XOR cu cheia gasita la primul pas pe intreaga imagine
		pop ebx
		mov [esp + 4], eax
		xor ecx, ecx

decrypt_using_old_key:
		cmp ecx, eax
		je compute_new_key
		mov edx, [edi + ecx]
		xor edx, ebx
		mov byte[edi + ecx], dl
		add ecx, 4
		jmp decrypt_using_old_key

compute_new_key:
		pop ecx ; valoarea fostei chei de criptare
		; noua cheie va fi
		; new_key = floor((2 * old_key + 3) / 5) - 4
		xor eax, eax
		mov eax, ebx
		push ebx
		mov ebx, 2
		mul ebx
		add eax, 3
		mov ebx, 5
		div ebx
		sub eax, 4 ; in eax avem acum noua cheie
		pop ebx

		; incepem criptarea mesajului cu noua cheie
		call encrypt_message_task2

		; printam imaginea rezultata dupa criptare
		push DWORD[img_height]
		push DWORD[img_width]
		push DWORD[img]
		call print_image
		jmp done

solve_task3:
		; cautam offsetul care se afla dupa spatiu
		mov eax, [ebp + 12]
		mov edi, [eax] ; in edi avem argumentele
		mov ecx, 28

search_offset_value_task3:
		inc ecx
		cmp byte[edi + ecx], 0x00
		jne search_offset_value_task3

		mov ebx, ecx
		mov eax, [ebp + 12]
		push DWORD[eax + 16]
		call atoi
		add esp, 4

		push 0x00
		mov ecx, ebx
		dec ecx
start_crypting_task3:
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
		cmp byte[edi + ecx], "0"
		je crypt_0
		cmp byte[edi + ecx], "1"
		je crypt_1
		cmp byte[edi + ecx], "2"
		je crypt_2
		cmp byte[edi + ecx], "3"
		je crypt_3
		cmp byte[edi + ecx], "4"
		je crypt_4
		cmp byte[edi + ecx], "5"
		je crypt_5
		cmp byte[edi + ecx], "6"
		je crypt_6
		cmp byte[edi + ecx], "7"
		je crypt_7
		cmp byte[edi + ecx], "8"
		je crypt_8
		cmp byte[edi + ecx], "9"
		je crypt_9
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

crypt_0:
		push " "
		push "-"
		push "-"
		push "-"
		push "-"
		push "-"
		dec ecx
		jmp start_crypting_task3

crypt_1:
		push " "
		push "-"
		push "-"
		push "-"
		push "-"
		push "."
		dec ecx
		jmp start_crypting_task3

crypt_2:
		push " "
		push "-"
		push "-"
		push "-"
		push "."
		push "."
		dec ecx
		jmp start_crypting_task3

crypt_3:
		push " "
		push "-"
		push "-"
		push "."
		push "."
		push "."
		dec ecx
		jmp start_crypting_task3

crypt_4:
		push " "
		push "-"
		push "."
		push "."
		push "."
		push "."
		dec ecx
		jmp start_crypting_task3

crypt_5:
		push " "
		push "."
		push "."
		push "."
		push "."
		push "."
		dec ecx
		jmp start_crypting_task3

crypt_6:
		push " "
		push "."
		push "."
		push "."
		push "."
		push "-"
		dec ecx
		jmp start_crypting_task3

crypt_7:
		push " "
		push "."
		push "."
		push "."
		push "-"
		push "-"
		dec ecx
		jmp start_crypting_task3

crypt_8:
		push " "
		push "."
		push "."
		push "-"
		push "-"
		push "-"
		dec ecx
		jmp start_crypting_task3

crypt_9:
		push " "
		push "."
		push "-"
		push "-"
		push "-"
		push "-"
		dec ecx
		jmp start_crypting_task3

start_writing_message_task3:
		mov edi, [img]
		mov ebx, 4
		mul ebx

iteration_writing_message_task3:
		pop ebx
		cmp ebx, 0
		je end_message_task3
		mov	byte[edi + eax], bl
		add eax, 4
		jmp iteration_writing_message_task3

end_message_task3:
		sub eax, 4
		mov byte[edi + eax], 0

		push DWORD[img_height]
		push DWORD[img_width]
		push DWORD[img]
		call print_image
		add esp, 12

    jmp done

solve_task4:
		; in eax memoram offsetul de la care trebuie sa incepem
		mov eax, [ebp + 12]
		push DWORD[eax + 16]
		call atoi
		add esp, 4
		mov ebx, 4
		mul ebx
		sub eax, 4
		; in edi memoram adresa imaginii
		mov edi, [img]
		xor edx, edx
		mov edx, -1
		; in esi avem stringul ce trebuie codificat
		mov esi, [ebp + 12]
		mov esi, [esi + 12]

crypt_word_task4:
		xor ecx, ecx
		add edx, 1
		cmp byte[esi + edx], 0
		je final_byte_task4

crypt_single_byte_task4:
		cmp ecx, 8
		je crypt_word_task4
		xor ebx, ebx
		mov bl, [esi + edx]
		shl bl, cl
		and bl, 128
		shr bl, 7
		cmp bl, 0
		je crypt_0_task4
		cmp bl, 1
		je crypt_1_task4

crypt_0_task4:
		push ecx
		xor ecx, ecx
		mov ecx, [edi + eax]
		and cl, 254
		mov byte[edi + eax], cl
		add eax, 4
		pop ecx
		inc ecx
		jmp crypt_single_byte_task4

crypt_1_task4:
		push ecx
		xor ecx, ecx
		mov ecx, [edi + eax]
		or cl, 1
		mov byte[edi + eax], cl
		add eax, 4
		pop ecx
		inc ecx
		jmp crypt_single_byte_task4

final_byte_task4:
		xor ecx, ecx

writing_null_terminator_task4:
		cmp ecx, 8
		je print_result_task4
		xor ebx, ebx
		mov bl, byte[edi + eax]
		and ebx, 254
		mov byte[edi + eax], bl
		add eax, 4
		inc ecx
		jmp writing_null_terminator_task4

print_result_task4:
		; afisam imaginea rezultata
		push DWORD[img_height]
		push DWORD[img_width]
		push DWORD[img]
		call print_image
    jmp done

solve_task5:
		; in eax memoram offsetul de la care sa incepem
		mov eax, [ebp + 12]
		push DWORD[eax + 12]
		call atoi
		add esp, 4
		mov ebx, 4
		mul ebx
		; in edi memoram adresa imaginii in care incepem cautarea
		mov edi, [img]
		; in ebx vom memora mesajul primit
		xor ebx, ebx
		push 1

start_decryption_task5:
		pop ecx
		cmp ecx, 0
		je done_task5
		xor ecx, ecx
		push ecx
		; mov ecx, 1

decrypt_single_byte_task5:
		cmp ecx, 8
		je print_decrypted_message_task5
		xor edx, edx
		mov edx, [edi + eax]
		shl dl, 7
		shr dl, cl
		shr dl, 1
		or ebx, edx
		mov [esp], ebx
		inc ecx
		add eax, 4
		jmp decrypt_single_byte_task5

print_decrypted_message_task5:
		cmp ebx, 0 ; nu vrem sa afisam si null terminator
		je done_task5
		PRINT_CHAR ebx ; afisam litera curenta
		xor ebx, ebx
		jmp start_decryption_task5

done_task5:
		NEWLINE
    jmp done

solve_task6:

		mov eax, [img_width]
		mov ebx, [img_height]
		mul ebx
		mov ebx, 4
		mul ebx
		; PRINT_DEC 4, eax
		; NEWLINE
		; in eax avem nr maxim de octeti din imagine
		mov ecx, eax

		mov eax, 45
		mov ebx, 0
		int 0x80

		mov esi, eax ; inceputul zonei de heap

		mov eax, 45
		mov ebx, esi
		add ebx, ecx
		int 0x80

		; esi acum pointeaza catre zona de heap alocata

		mov edi, [img]
		; mov ecx, 1

; start_new_line_task6:
; 		mov ebx, 2
		; mov eax, 0
		; push eax
		mov eax, 1
		mov ebx, [img_width]
		mul ebx
		mov ebx, 4
		mul ebx
		add eax, 4 ; offsetul primului pixel de la care trebuie sa bluram
		mov ebx, 2
		push ebx
		mov edx, 0

		; PRINT_DEC 4, [edi + eax]
		; NEWLINE

blur_one_line_task6:
		cmp ebx, [img_width]
		je skip_line_task6
		inc ebx
		; push ebx
		xor ecx, ecx
		; ; add cl, byte[edi + eax]
		; ; add cl, byte[edi + eax + 4]
		; ; add cl, byte[edi + eax - 4]
		; PRINT_DEC 4, [edi + eax]
		; PRINT_STRING " "
		add ecx, [edi + eax]
		add ecx, [edi + eax + 4]
		add ecx, [edi + eax - 4]
		push eax
		sub eax, [img_width]
		sub eax, [img_width]
		sub eax, [img_width]
		sub eax, [img_width]
		add ecx, [edi + eax]
		; mov eax, [esp + 4]
		add eax, [img_width]
		add eax, [img_width]
		add eax, [img_width]
		add eax, [img_width]
		add eax, [img_width]
		add eax, [img_width]
		add eax, [img_width]
		add eax, [img_width]
		add ecx, [edi + eax]
		push edx
		mov eax, ecx
		push ebx
		xor edx, edx
		mov ebx, 5
		div ebx

		pop ebx
		pop edx
		; push ecx
		; mov ecx, eax
		; mov eax, [img_width]
		; push ebx
		; mov ebx, 4
		; mul ebx
		; neg eax
		; add eax, ecx
		; pop ebx
		; pop ecx
		; add ecx, [edi + eax]
		; push ecx
		; mov ecx, eax
		; mov eax, [img_width]
		; push ebx
		; mov ebx, 8
		; mul ebx
		; neg eax
		; add eax, ecx
		; pop ebx
		; pop ecx
		; add ecx, [edi + eax]
		; mov eax, ecx
		; push edx
		; xor edx, edx
		; push ebx
		; mov ebx, 5
		; div ebx
		;
		; ; PRINT_DEC 4, eax
		; ; PRINT_CHAR " "
		; pop ebx
		; pop edx
		mov [esi + edx], eax
		add edx, 4
		; PRINT_DEC 4, [esi + edx - 4]

		; PRINT_DEC 4, eax
		; PRINT_STRING " "
		; ; push eax
		; ; mov eax, [ebp - 4]
		; ; mov byte[esi + eax], cl
		pop eax
		add eax, 4
		jmp blur_one_line_task6

skip_line_task6:
		; add eax, 4
		pop ebx
		inc ebx
		cmp ebx, [img_height]
		je finish_blur
		; inc ebx
		; PRINT_DEC 4, ebx
		; PRINT_STRING " "
		; NEWLINE
		push ebx
		mov ebx, 2
		add eax, 8
		jmp blur_one_line_task6

finish_blur:
		; TODO copy values to image

		mov eax, 1
		mov ebx, [img_width]
		mul ebx
		mov ebx, 4
		mul ebx
		add eax, 4 ; offsetul primului pixel de la care trebuie sa bluram
		mov ebx, 2
		push ebx
		xor ecx, ecx

		; PRINT_DEC 4, eax
		; NEWLINE
write_new_blurred_line:
		cmp ebx, [img_width]
		je check_end_blur
		inc ebx
		mov edx, [esi + ecx]
		mov byte[edi + eax], dl
		; PRINT_DEC 1, edx
		; NEWLINE
		add ecx, 4
		add eax, 4
		jmp write_new_blurred_line

check_end_blur:
		pop ebx
		inc ebx
		cmp ebx, [img_height]
		je write_result_task6
		push ebx
		mov ebx, 2
		add eax, 8
		jmp write_new_blurred_line
				; PRINT_DEC 4, edx
				; NEWLINE


write_result_task6:
		; add esp, 8
		; mov ebp, esp

		push DWORD[img_height]
		push DWORD[img_width]
		push DWORD[img]
		call print_image
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
