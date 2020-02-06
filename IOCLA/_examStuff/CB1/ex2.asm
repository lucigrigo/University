%include "io.inc"

section .data
    a dd 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    N dd 10
    k dd 15
    arr resd 10

section .text

print:
    push ebp
    mov ebp, esp

    mov eax, dword[ebp + 8]
    mov ecx, dword[ebp + 12]
    xor edx, edx
iter:
    mov ebx, dword[eax + 4 * edx]
    PRINT_DEC 4, ebx
    PRINT_STRING ", "
    inc edx
    cmp edx, ecx
    jne iter
    NEWLINE

    leave
    ret

compute:
    push ebp
    mov ebp, esp
    
    mov eax, dword[ebp + 8]
    mov ebx, eax
    add ebx, 10
    mul ebx
    
    leave
    ret

global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    
    ; a)
    PRINT_STRING "A)"
    NEWLINE
    
    push dword[N]
    push dword a
    call print
    add esp, 8

    ; b)
    push dword[k]
    call compute
    add esp, 4
    
    PRINT_STRING "B)"
    NEWLINE
    PRINT_DEC 4, eax
    NEWLINE
    
    ; c)
    PRINT_STRING "C)"
    NEWLINE
    mov eax, dword[N]
    mov ebx, 4
    mul ebx
    sub esp, eax
    xor ebx, ebx
iter_arr:
    push ebx
    call compute
    pop ebx

    mov dword[esp + 4 * ebx], eax
    inc ebx
    cmp ebx, dword[N]
    jl iter_arr
    
    xor ebx, ebx
print_arr:
    mov eax, dword[esp + 4 * ebx]
    PRINT_DEC 4, eax
    PRINT_STRING ", "
    inc ebx
    cmp ebx, dword[N]
    jl print_arr
    NEWLINE
    
    push dword [N]
    mov eax, esp
    add eax, 4
    push eax
    call print
    add esp, 8
    NEWLINE
    
    xor eax, eax
    leave
    ret