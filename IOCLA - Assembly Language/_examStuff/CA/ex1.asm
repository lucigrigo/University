%include "io.inc"

section .data
    num dd 51

section .text

global CMAIN

CMAIN:
    push ebp
    mov ebp, esp
    
    ; a)
    mov eax, dword[num]
    shl eax, 27
    shr eax, 27
    cmp eax, 31
    jne fail_set
    
    PRINT_STRING "primii 5 biti sunt setati"
    jmp done_a
    
fail_set:
    PRINT_STRING "un bit nu este setat"
    jmp done_a
    
done_a:
    NEWLINE


    ; b)
    xor ecx, ecx
iter_check_set:
    mov eax, dword[num]
    mov ebx, 31
    sub ebx, ecx
    push ecx
    
    xor ecx, ecx
shift_left:
    shl eax, 1
    inc ecx
    cmp ecx, ebx
    jl shift_left
    
    xor ecx, ecx
shift_right:
    shr eax, 1
    inc ecx
    cmp ecx, 31
    jl shift_right
    
    pop ecx
    cmp eax, 1
    jne next_iter
    
    PRINT_DEC 4, ecx
    PRINT_STRING " "
next_iter:
    inc ecx
    cmp ecx, 32
    jl iter_check_set
    NEWLINE
    
    ; c)
    mov eax, dword[num]
    xor edx, edx
    mov edx, 31
    xor ebx, ebx
    inc ebx
    shl ebx, 31
find_start:
    mov ecx, eax
    and ecx, ebx
    cmp ecx, 0
    jne found_start
    dec edx
    shr ebx, 1
    jmp find_start
    
found_start:
    ; ebx = ...0010...
    ; edx = indice n ( 2 * n )
    
    xor edx, edx
    mov edx, 1
    shr ebx, 1
verif_palindrom:
    push ebx
    mov ecx, eax
    and ecx, ebx
    cmp ecx, 0
    je verif_0
    
verif_1:
    mov ebx, eax
    and ebx, edx
    cmp ebx, 0
    je not_pal
    jmp next_iter_pal
    
verif_0:
    ; no need to check 0 as well if we already check 1
    jmp next_iter_pal
    
next_iter_pal:
    pop ebx
    shl edx, 1
    add edx, 1
    shr ebx, 1
    cmp ebx, 0
    jg verif_palindrom
    
    PRINT_STRING "Numarul este palindrom"
    jmp done_c
    
not_pal:
    PRINT_STRING "Numarul NU este palindrom"
    jmp done_c
    
done_c:
    NEWLINE

    xor eax, eax
    leave
    ret