%include "io.inc"

section .data
    ; TODO a: Define arr1, arr2 and res arrays.
    arr1 dd 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    arr2 dd 30, 35, 40, 45, 50, 55, 60, 55, 60, 65

section .bss
    res resd 10
    
section .rodata
    num dd 10

section .text
global main

main:
    push ebp
    mov ebp, esp


    ; TODO b: Compute res[0] and res[n-1].
    ; res[0]
    xor eax, eax
    mov eax, [arr1]
    add eax, [arr2 + 36]
    mov [res], eax
    ; res[n-1]
    xor eax, eax
    mov eax, [arr1 + 36]
    add eax, [arr2]
    mov [res + 36], eax

    ; List first and last item in each array.
    PRINT_UDEC 4, [arr1]
    NEWLINE
    PRINT_UDEC 4, [arr2]
    NEWLINE
    PRINT_UDEC 4, [res]
    NEWLINE

    PRINT_UDEC 4, [arr1+36]
    NEWLINE
    PRINT_UDEC 4, [arr2+36]
    NEWLINE
    PRINT_UDEC 4, [res+36]
    NEWLINE


    ; TODO d: Compute cross sums in res[i].
    xor ecx, ecx
compute_cross_sum:
    xor eax, eax
    add eax, [arr1 + 4 * ecx]
    mov ebx, ecx
    neg ebx
    add eax, [arr2 + 36 + 4 * ebx]
    mov [res + 4 * ecx], eax
    
    inc ecx
    cmp ecx, [num]
    jl compute_cross_sum

    ; TODO c: List arrays.
    xor ecx, ecx
print_arrays:
    PRINT_UDEC 4, [arr1 + 4 * ecx]
    PRINT_STRING " + "
    mov ebx, ecx
    neg ebx
    PRINT_UDEC 4, [arr2 + 36 + 4 * ebx]
    PRINT_STRING " = "
    PRINT_UDEC 4, [res + 4 * ecx]
    NEWLINE
    
    inc ecx
    cmp ecx, [num]
    jl print_arrays

    ; Return 0.    
    xor eax, eax
    leave
    ret