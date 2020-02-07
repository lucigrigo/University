%include "io.inc"

%define ARRAY_SIZE 13
%define DECIMAL_PLACES 5

section .data
    num_array dw 76, 12, 65, 19, 781, 671, 431, 761, 782, 12, 91, 25, 9
    array_sum_prefix db "Sum of numbers: ",0
    array_mean_prefix db "Numbers mean: ",0
    decimal_point db ".",0
    mul_ten dw 10

section .text
global CMAIN
CMAIN:
    xor eax, eax
    xor edx, edx
    mov ecx, ARRAY_SIZE
    
    ; TODO1 - compute the sum of the vector numbers - store it in ax
start:
    add ax, word [num_array + 2 * (ecx - 1)]
    loop start   

    PRINT_STRING array_sum_prefix
    PRINT_UDEC 2, ax
    NEWLINE

    ; TODO2 - compute the quotient of the mean
    mov ecx, ARRAY_SIZE
    div ecx
    PRINT_STRING array_mean_prefix
    PRINT_UDEC 2, ax
    PRINT_STRING decimal_point
    
    
    mov ebx, ARRAY_SIZE
    mov ecx, DECIMAL_PLACES
compute_decimal_place:

    ; TODO3 - compute the current decimal place - store it in ax
    mov ax, dx
    mul word [mul_ten]
    div ebx
    PRINT_UDEC 2, ax
    dec ecx
    cmp ecx, 0
    jg compute_decimal_place

    NEWLINE

    xor eax, eax
    ret
