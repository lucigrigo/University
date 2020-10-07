%include "io.inc"

section .data
    param_a dd 15
    param_b dd 4
    size dd 6
    arr dd 1,2,3,4,5,6
    k dd 4

section .text

mul:
    push ebp
    mov ebp, esp
    
    mov eax, dword[ebp + 8]
    mov ecx, dword[ebp + 12]
    
    mov ebx, 7
    mul ebx
    add eax, ecx
    
    leave
    ret
    
apply:  
    push ebp
    mov ebp, esp
    
    mov eax, dword[ebp + 8] ; array
    mov ecx, dword[ebp + 12] ; size
    mov ebx, dword[ebp + 16] ; scalar
    xor edx, edx
iter_apply:
    push ebx
    push ecx
    push edx
    push eax
    
    mov ecx, dword[eax + 4 * edx]
    push ebx
    push ecx
    call mul
    add esp, 8
    
    mov ecx, eax
    pop eax
    pop edx
    mov dword[eax + 4 * edx], ecx
    
    PRINT_DEC 4, dword eax + 4 * edx
    NEWLINE
    pop ecx
    pop ebx
    inc edx
    cmp edx, ecx
    jne iter_apply
    
    leave
    ret

global CMAIN

CMAIN:
    push ebp
    mov ebp, esp
    
    ; a)
    push dword[param_b]
    push dword[param_a]
    call mul
    add esp, 8
    
    PRINT_DEC 4, eax
    NEWLINE
    
    ; b) - already done
    
    ; c)
    push dword[k]
    push dword[size]
    push dword arr
    call apply
    add esp, 12
    
    xor eax, eax
    leave
    ret