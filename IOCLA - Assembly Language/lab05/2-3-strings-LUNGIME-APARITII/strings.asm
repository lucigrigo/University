%include "io.inc"

section .data
    string db "Lorem ipsum dolor sit amet.", 0
    print_strlen db "strlen: ", 10, 0
    print_occ db "occurences of `i`:", 10, 0

    occurences dd 0
    length dd 0    
    char db 'i'

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    
    ; TODO1: compute the length of a string
    mov al, 0
    mov edi, string
    
    ; TODO1: save the result in at address length
    repne scasb

    sub edi, string  
    dec edi
    
    mov [length], edi
    ; print the result of strlen
    PRINT_STRING print_strlen
    PRINT_UDEC 4, [length]
    NEWLINE

    ; TODO2: compute the number of occurences
    xor edx, edx
    mov ecx, [length]
    
    mov al, [char]
    mov edi, string
    
start:
    inc edx
    repne scasb
    
    cmp ecx, 0
    jg start
    ; TODO2: save the result in at address occurences
    dec edx
    mov [occurences], edx
    ; print the number of occurences of the char
    PRINT_STRING print_occ
    PRINT_UDEC 4, [occurences]
    NEWLINE

    xor eax, eax
    leave
    ret
