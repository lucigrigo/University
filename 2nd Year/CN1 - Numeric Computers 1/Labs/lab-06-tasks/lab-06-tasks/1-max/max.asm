%include "io.inc"

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    ; cele doua numere se gasesc in eax si ebx
    mov eax, 42
    mov ebx, 11 

    ; TODO: aflati maximul folosind doar o instructiune de salt si push/pop
    cmp eax, ebx
    jge print
    push eax
    push ebx
    pop eax
    pop ebx
print:
    PRINT_DEC 4, eax ; afiseaza maximul
    NEWLINE

    leave
    ret
