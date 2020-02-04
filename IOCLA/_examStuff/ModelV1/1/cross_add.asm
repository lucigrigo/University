%include "io.inc"

section .data
    ; TODO a: Define arr1, arr2 and res arrays.


section .bss
    res resd 10

section .text
global main

main:
    push ebp
    mov ebp, esp


    ; TODO b: Compute res[0] and res[n-1].



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



    ; TODO c: List arrays.



    ; Return 0.    
    xor eax, eax
    leave
    ret