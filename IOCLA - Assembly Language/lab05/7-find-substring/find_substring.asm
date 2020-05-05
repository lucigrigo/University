%include "io.inc"

section .data
source_text: db "ABCABCBABCBABCBBBABABBCBABCBAAACCCB", 0
substring: db "BABC", 0

source_length: resd 1
substr_length: dd 4

print_format: db "Substring found at index: ", 0

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    ; TODO: Fill source_length with the length of the source_text string.
    ; Find the length of the string using scasb.
    cld
    mov al, 0x00
    mov edi, source_text
    repne scasb
    
    sub edi, source_text
    dec edi
    
    mov [source_length], edi
    
    ; TODO: Print the start indices for all occurrences of the substring in source_text
    mov ecx, [source_length]
    mov edi, source_text
    mov al, "B"
    
findB:
    repne scasb
    
    ;am gasit urmatorul b
    mov edx, [source_length]
    sub edx, ecx ;indicele la care incepe subtring in source_text
    
    push edi
    push ecx
    
    mov esi, substring + 1
    mov ecx, 4
    repe cmpsb
    
    cmp ecx, 0
    jne notFound
    
    PRINT_STRING "String gasit la indicele: "
    PRINT_UDEC 4, edx
    NEWLINE
    
notFound:
    pop ecx
    pop edi
    
    cmp ecx, 0
    jg findB  
    
    leave
    ret