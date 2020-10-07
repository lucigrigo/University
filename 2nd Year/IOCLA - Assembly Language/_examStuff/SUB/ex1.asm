%include "io.inc"
extern printf

section .data
    num dq 3.51
    format_q db "%f", 10, 0
    string db "ana are mere.", 10, 0
    
section .text

global CMAIN

CMAIN:
    push ebp
    mov ebp, esp
    
    ; a) - already done
    
    ; b)    
    xor ecx, ecx
    xor edx, edx
    mov al, byte[string]
iter_string:
    ;PRINT_CHAR al
    cmp al, 65
    je found_aA
    cmp al, 97
    je found_aA
    
    inc edx
    jmp next_iter
    
found_aA:
    push eax
    mov esi, [string + ecx + 1]
    mov edi, [string + edx]

    push ecx
    push eax
iter_overwrite:
    mov al, byte [string + ecx + 1]
    mov byte[string + ecx], al
    inc ecx
    cmp ecx, 12
    jne iter_overwrite
    
    pop eax
    pop ecx
    
next_iter:
    inc ecx
    mov al, byte[string + ecx]
    cmp al, 10
    jne iter_string
    
    
put_aA:
    pop eax
    mov byte[string + edx], al
    inc edx
    cmp esp, ebp
    jne put_aA
    
    PRINT_STRING string
    
    ; c)
    NEWLINE
    fld qword[num]
    frndint
    sub esp, 8
    fstp qword[esp]
    
    ;PRINT_DEC 4, dword esp + 4
    ;PRINT_DEC 4, dword esp
    ;NEWLINE
    push format_q
    call printf
    add esp, 12
    
    xor eax, eax
    leave
    ret