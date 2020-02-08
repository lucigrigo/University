%include "io.inc"

section .data
    ; TODO a
    ;a dd 0x03
    ;i db 7
    a dd 0x55
    i db 2
    ;a dd 0x5
    ;i db 31

    ; TODO b
    ;b dd 0x83
    ;j db 7
    ;b dd 0x11
    ;j db 2
    b dd 0xF8001234
    j db 27

    ; TODO c
    L db 8
    ;L db 0
    ;L db 31

section .text
global main

main:
    push ebp
    mov ebp, esp

    ; TODO a: set bit i of integer a and print the result
    xor eax, eax
    mov eax, 1
    xor ecx, ecx
shift_mask_a:
    shl eax, 1
    inc ecx
    cmp cl, byte[i]
    jl shift_mask_a
    
    mov ebx, dword[a]
    or ebx, eax
    
    PRINT_STRING "a) new nr = "
    PRINT_HEX 4, ebx
    NEWLINE

    ; TODO b: clear bit j of integer b and print the result
    
    xor eax, eax
    mov eax, 1
    xor ecx, ecx
shift_mask_b:
    shl eax, 1
    inc ecx
    cmp cl, byte[j]
    jl shift_mask_b
    
    mov edx, eax
    xor eax, eax
    mov eax, 1
    shl eax, 31
    dec eax
    sub eax, edx
    
    mov ebx, dword[b]
    and ebx, eax
    
    PRINT_STRING "b) output nr = "
    PRINT_HEX 4, ebx
    NEWLINE

    ; TODO c: generate a mask with first L bits set and the rest cleared L can be one of {0, 1, .. 31}. Print the result
    ; e.g: L = 8, mask = 0x000000FF
    xor eax, eax
    xor ecx, ecx
create_mask_c:
    cmp cl, byte[L]
    je done_mask_c
    shl eax, 1
    add eax, 1
    inc ecx
    jmp create_mask_c
    
done_mask_c:
    PRINT_STRING "c) mask = "
    PRINT_HEX 4, eax
    NEWLINE

    ; Return 0
    xor eax, eax
    leave
    ret
