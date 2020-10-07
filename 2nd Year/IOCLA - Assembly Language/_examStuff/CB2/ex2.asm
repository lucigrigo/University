%include "io.inc"

section .data
    arr dd 1,2,3,4,5
    size dd 5
    dest resd 5

section .text

print_arr:
    push ebp
    mov ebp, esp
    
    mov eax, dword[ebp + 8]
    mov ecx, dword[ebp + 12]
    xor edx, edx
iter_print:
    mov ebx, dword[eax + 4 * edx]
    PRINT_UDEC 4, ebx
    PRINT_CHAR " "
    inc edx
    cmp edx, ecx
    jne iter_print
    NEWLINE
    
    leave
    ret
    
sum_adj:
    push ebp
    mov ebp, esp
    
    ; dest[i] = a[i] + a[i + 1]
    mov ecx, dword[ebp + 16]
    dec ecx
    mov ebx, dword[ebp + 12] ; ebx = dest
    mov eax, dword[ebp + 8] ; eax = a
    xor edx, edx
compute_adj_sum:
    push ecx
    mov ecx, dword[eax + 4 * edx]
    add ecx, dword[eax + 4 * edx + 4]
    mov dword[ebx + 4 * edx], ecx
    
    pop ecx
    inc edx
    cmp edx, ecx
    jne compute_adj_sum
    
    mov ecx, dword[eax + 4 * edx]
    add ecx, dword[eax]
    mov dword[ebx + 4 * edx], ecx
    
    leave
    ret
    
sum_inplace:
    push ebp
    mov ebp, esp
    
    mov ecx, dword[ebp + 12]
    dec ecx
    mov eax, dword[ebp + 8]
    xor edx, edx
    push dword[eax]
iter_inplace:
    xor ebx, ebx
    mov ebx, dword[eax + 4 * edx]
    add ebx, dword[eax + 4 * edx + 4]
    mov dword[eax + 4 * edx], ebx
    inc edx
    cmp edx, ecx
    jne iter_inplace
    
    pop ebx
    add dword[eax + 4 * edx], ebx
    leave
    ret
    
global CMAIN

CMAIN:
    push ebp
    mov ebp, esp
    
    ; a)
    push dword[size]
    push dword arr
    call print_arr
    add esp, 8
    
    ; b)
    push dword[size]
    push dword dest
    push dword arr
    call sum_adj
    add esp, 12
    
    push dword[size]
    push dword dest
    call print_arr
    add esp, 8
    
    ; c)
    push dword[size]
    push dword arr
    call sum_inplace
    add esp, 8
    
    push dword[size]
    push dword arr
    call print_arr
    add esp, 8
    
    xor eax, eax
    leave
    ret