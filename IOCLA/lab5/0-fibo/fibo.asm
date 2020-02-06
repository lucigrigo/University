%include "io.inc"
section .data
    N dd 9 ; compute the sum of the first N fibonacci numbers
    var dd ? ; variabila de lucru
section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    ; TODO: calculate the sum of first N fibonacci numbers
    ;       (f(0) = 0, f(1) = 1)
    ;       store the sum in eax
    ;       use loop instruction 

    mov ecx, [N]
    mov ebx, 0
    mov edx, 1
    xor eax, eax
    ;sub ecx, 1
while:
    add eax, ebx
    mov [var], ebx
    mov ebx, edx
    add edx, [var]
    sub ecx, 1
    cmp ecx, 0
    jg while

    PRINT_STRING "Sum first "
    PRINT_DEC 4, [N]
    PRINT_STRING " fibo is "
    PRINT_UDEC 4, eax

    xor eax, eax
    leave
	ret
