%include "io.inc"

extern printf

%DEFINE LENGTH 20

section .data
    string db "Nunc tristique ante maximus, dictum nunc in, ultricies dui.", 0
    char db 'a'

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp

    ; TODO: set al to the char to memset with;
    mov al, 'a'
    ; TODO: set edi to point to the destination string
    mov edi, string
    ; TODO: set ecx to the number of times stosb will be performed
    mov ecx, 20
    ; TODO: use a stosb loop to store to string; use no more than 1 instruction
    repne stosb
    ; print the string
    PRINT_STRING string

    xor eax, eax
    leave
    ret
