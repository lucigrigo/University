%include "io.inc"

section .data
    vector dq 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9
    n      dd ($-vector)/8
    format db "Media elementelor: %f", 10, 0

section .text
    global CMAIN

extern printf

CMAIN:
    ; incarca valoarea 0 pe stiva FPU
    fldz

    ; TODO: parcurgerea tuturor elementelor si adunare la valoarea din varful stivei FPU
    mov eax, vector
    mov ecx, dword[n]
add_loop:
    cmp ecx, 0
    je calc_med    

    fadd qword[eax]
    add eax, 8
    
    dec ecx
    jmp add_loop

    ; TODO: impartirea sumei la numarul de elemente
calc_med:
    fidiv dword[n]

    ; TODO Afisarea rezultatului
    sub esp, 8
    fstp qword[esp]
    
    push format
    call printf
    add esp, 12

    xor eax, eax
    ret
