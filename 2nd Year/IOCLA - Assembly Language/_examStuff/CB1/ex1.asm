%include "io.inc"

section .data
    a dd 7
    N dd 35
    res32 resd 0
    x dd 31
    y dd 32
    k dd 16
    high resd 0
    low resd 0
    
section .text

global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    
    ; a)
    ; ridicarea la putere
    xor ecx, ecx
    mov eax, 1
power:
    shl eax, 1
    inc ecx
    cmp ecx, dword[N]
    jl power
    
    ;inmultirea cu scalarul
    mov ebx, dword[a]
    mul ebx
    
    ; salvare rezultat
    mov dword[res32], eax
    
    ; afisare rezultat a * 2 ^ N
    PRINT_STRING "a) a * 2 ^ N = "
    PRINT_UDEC 4, eax
    NEWLINE
    
    
    ; b)
    mov eax, dword[x]
    mov ecx, dword[k]
    mov ebx, 32
    sub ebx, ecx
    push ebx
select_most_sign:
    shr eax, 1
    dec ebx
    cmp ebx, 0
    jge select_most_sign
    
    pop ebx
    push eax
    push ebx
    mov eax, dword[y]
select_least_sign:
    shr eax, 1
    dec ebx
    cmp ebx, 0
    jge select_least_sign
    
    pop ebx
restore_second_nr:
    shl eax, 1
    dec ebx
    cmp ebx, 0
    jge restore_second_nr
    
    pop ecx
    or eax, ecx
    
    PRINT_STRING "b) nr = "
    PRINT_DEC 4, eax
    NEWLINE
    
    
    ;c)
    mov ecx, dword[N]
    xor eax, eax
    xor ebx, ebx
    inc ebx
    clc
compute_power:
    shl eax, 1
    shl ebx, 1
    jc set_high
    
continue_compute:
    dec ecx
    cmp ecx, 0
    jne compute_power
    
    jmp done_c
    
set_high:
    mov eax, 1
    xor ebx, ebx
    jmp continue_compute
   
done_c:
    push ebx
    mov ebx, dword[a]
    mul ebx
    pop ebx
    
    push eax
    mov eax, ebx
    ;push eax
    mov ebx, dword[a]
    mul ebx
    pop ebx
    ;pop eax
    

    PRINT_STRING "c) "
    NEWLINE
    PRINT_DEC 4, ebx
    NEWLINE
    PRINT_DEC 4, eax
    NEWLINE
    
    xor eax, eax
    leave
    ret