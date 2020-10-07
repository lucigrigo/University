%include "io.inc"

section .data
   word_num1 dd 0xff543210
   word_num2 dd 0x00111111
   result_word resd 2
   big_num1 dd 0x11111111, 0x22222222, 0x33333333
   big_num2 dd 0xffffffff, 0x22222222, 0x33333333
   result_4word resd 4
   num_array1 dd 0x11111111, 0x22222222, 0x33333333, 0x12111211, 0x22232242, 0xff333333, 0xff123456, 0xff123456, 0xff123456
   num_array2 dd 0xffffffff, 0x22922252, 0x33033338, 0x12111211, 0x22232242, 0xff333333, 0xff123456, 0xff123456, 0xff123456
   result_array resd 12
   length dd 3

section .text
global main
main:
    push ebp
    mov ebp, esp

    ;TODO a, b, c: Implement the array sum starting with double word sum incrementally solving subsequent task b and c.
    ; a)
    mov eax, dword[word_num1]
    shl eax, 16
    shr eax, 16
    mov ebx, dword[word_num2]
    shl ebx, 16
    shr ebx, 16
    clc
    add eax, ebx
    jnc move_lower_a
    add dword[result_word], 1
move_lower_a:
    mov dword[result_word + 4], eax
    mov eax, dword[word_num1]
    mov ebx, dword[word_num2]
    shr ebx, 16
    shr eax, 16
    add eax, ebx
    add dword[result_word], eax
    
    ; b)
    mov eax, dword[big_num1 + 8]
    mov ebx, dword[big_num2 + 8]
    clc
    add eax, ebx
    jnc move_first_b
    add dword[result_4word + 8], 1
move_first_b:
    mov dword[result_4word + 12], eax
    mov eax, dword[big_num1 + 4]
    mov ebx, dword[big_num2 + 4]
    clc 
    add eax, ebx
    jnc move_second_b
    add dword[result_4word + 4], 1
move_second_b:
    mov dword[result_4word + 8], eax
    mov eax, dword[big_num1]
    mov ebx, dword[big_num2]
    clc 
    add eax, ebx
    jnc move_third_b
    add dword[result_4word], 1
move_third_b:
    mov dword[result_4word + 4], eax
    
    ; c) - idem
    
    ;PRINT_UDEC 4, result_4word
    ;NEWLINE
    ;PRINT_UDEC 4, [result_4word + 4]
    ;NEWLINE
    ;PRINT_UDEC 4, [result_4word + 8]
    ;NEWLINE
    ;PRINT_UDEC 4, [result_4word + 12]
    ;NEWLINE

    leave
    ret
