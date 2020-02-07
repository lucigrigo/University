%include "io.inc"
 
section .text
global CMAIN
CMAIN:
    mov eax, 4
    PRINT_UDEC 4, eax
    jmp exit            ; salt neconditionat catre label-ul exit
 
    mov eax, 7          ; codul acesta nu se executa
    mov ebx, 8
    add eax, ebx
    PRINT_UDEC 4, eax
 
exit:
    ret
