%include "io.inc"
 
section .text
global CMAIN
CMAIN:
    mov eax, zone2
    jmp eax             ; salt neconditionat catre adresa ce se afla in registrul eax
zone1:
    mov eax, 1
    mov ebx, 2
    add eax, ebx
    PRINT_UDEC 4, eax
    jmp exit
zone2:
    mov eax, 7
    mov ebx, 8
    add eax, ebx
    PRINT_UDEC 4, eax
    NEWLINE
    jmp $-0x174         ; salt relativ cu deplasamanent
exit:
    ret
