%include "io.inc"

%define ARRAY_SIZE 13
%define DECIMAL_PLACES 5

section .data
    num_array dw 76, 12, 65, 19, 781, 671, 431, 761, 782, 12, 91, 25, 9
    array_sum_prefix db "Sum of numbers: ",0
    array_mean_prefix db "Numbers mean: ",0
    decimal_point db ".",0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    xor eax, eax
    mov ecx, ARRAY_SIZE

    ; TODO1 - compute the sum of the vector numbers - store it in ax
    mov ebx, num_array
    mov edx, 0
iter:
    add eax, [ebx + edx * 2]
    inc edx
    cmp edx, 13
    jl iter
    
    PRINT_STRING array_sum_prefix
    PRINT_UDEC 2, ax
    NEWLINE

    ; TODO2 - compute the quotient of the mean
    mov cx, ARRAY_SIZE
    xor dx, dx
    div cx

    PRINT_STRING array_mean_prefix
    PRINT_UDEC 2, ax
    PRINT_STRING decimal_point

    xor eax, eax
    ret
