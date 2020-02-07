%include "io.inc"
 
section .text
global CMAIN
CMAIN:
    mov eax, 1
    mov ebx, 1
    cmp eax, ebx
    add ecx, 1   ; Comenteaza aceasta linie
    je print
    ret
print:
    PRINT_UDEC 4, eax
    ret
