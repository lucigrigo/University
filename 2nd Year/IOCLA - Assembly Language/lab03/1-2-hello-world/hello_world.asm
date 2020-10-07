%include "io.inc"

section .data
    myString: db "Hello, World!",0
    myStringGoodbye: db "Goodbye, World!",0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    mov ecx, 50                 ; N = valoarea registrului ecx
    mov eax, 2
    mov ebx, 1
    cmp eax, ebx
    jg print                   ; TODO1: eax > ebx?
    ret
    
print:

    cmp ecx, 0 
    jl goodbye

    PRINT_STRING myString
    NEWLINE
    
    dec ecx
    jmp print
                                   ; TODO2.2: afisati "Hello, World!" de N ori
goodbye:
    PRINT_STRING myStringGoodbye   ; TODO2.1: afisati "Goodbye, World!"

    ret
