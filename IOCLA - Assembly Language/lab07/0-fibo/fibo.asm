%include "io.inc"

%define NUM_FIBO 10

section .text
global CMAIN
CMAIN:
    mov ebp, esp

    ; TODO - replace below instruction with the algorithm for the Fibonacci sequence
    sub esp, NUM_FIBO * 4
    push 1
    push 0
    PRINT_DEC 4, [esp]
    NEWLINE
    PRINT_DEC 4, [esp + 4]
    NEWLINE

    mov ecx, NUM_FIBO
    sub ecx, 2
    ;
    ;
    ; 0   eax-0, ebx-1 ------------ eax-1, ebx-1 ----------------   ebx-1
    ; 1                                                             eax-1
for_loop:
    pop eax
    pop ebx
    add eax, ebx
    PRINT_DEC 4, eax
    NEWLINE
    push eax
    push ebx
    dec ecx
    cmp ecx, 0
    jg for_loop
    
    mov esp, ebp
    xor eax, eax
    ret
