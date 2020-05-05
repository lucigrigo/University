%include "io.inc"

section .data
    n1 dd 123   ;partea hi initiala
    n2 dd 2147483648    ;partea low initiala
    n dd 3
    hi db "hi ", 0
    low db "low ", 0
    
    
section .text
global CMAIN

CMAIN:
    mov eax, [n1]
    mov ebx, [n2]
    mov ecx, [n]
    
power:
    cmp ecx, 0
    je print
    dec ecx
    xor edx, edx
    inc edx
    shl edx, 31
    and edx, ebx
    shl ebx, 1
    shl eax, 1
    shr edx, 31
    add eax, edx
    jmp power
    
print:
    PRINT_STRING hi
    PRINT_UDEC 4, EAX
    NEWLINE
    PRINT_STRING low
    PRINT_UDEC 4, EBX
    
    xor eax, eax
    ret