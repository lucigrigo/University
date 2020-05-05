%include "io.inc"
section .data
left db "gdc(", 0

section .text
global CMAIN
CMAIN:
    ; input values (eax, edx): the 2 numbers to compute the gcd for
    mov ebp, esp
    mov eax, 49
    mov edx, 28
    mov ebx, eax
    mov ecx, edx
    push eax
    push edx
gcd:
    neg     eax
    je      L3

L1:
    neg     eax
    push eax
    push edx
    pop eax
    pop edx

L2:
    sub     eax,edx
    jg      L2
    jne     L1

L3:
    add     eax,edx
    jne     print
    inc     eax

print:

    ; TODO 1: solve the 'The program crashed!' error

    ; TODO 2: print the result in the form of: "gdc(eax, edx)=7"
    PRINT_STRING left
    PRINT_UDEC 4, ebx
    PRINT_STRING ","
    PRINT_UDEC 4, ecx
    PRINT_STRING ")="
    PRINT_UDEC 4, eax  ; output value in eax
    mov esp, ebp
    xor eax, eax
    ret