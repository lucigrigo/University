%include "io.inc"

section .data
    arr resd 10
    size dd 10

section .text

init_array:
    push ebp
    mov ebp, esp
    
    mov eax, dword[ebp + 8]
    mov ecx, dword[ebp + 12]
    xor edx, edx
iter_init:
    mov ebx, edx
    inc ebx
    push eax
    push edx
    
    xor edx, edx
    mov eax, ebx
    mul ebx
    mul ebx
    mov ebx, eax
    
    pop edx
    pop eax
    
    mov dword[eax + 4 * edx], ebx
    PRINT_STRING "arr["
    PRINT_DEC 4, edx
    PRINT_STRING "] = "
    PRINT_DEC 4, dword eax + 4 * edx
    NEWLINE
    
    inc edx
    cmp edx, ecx
    jne iter_init
    
    leave
    ret

global CMAIN

CMAIN:
    push ebp
    mov ebp, esp
    
    ; a) - already done
    
    ; b)
    push dword[size]
    push dword arr
    call init_array
    add esp, 8
    
    ; c) - already done
    
    xor eax, eax
    leave
    ret