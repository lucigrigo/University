%include "io.inc"
extern printf

section .data
    num1 dq 25.5
    num2 dq 17.3
    format db "%.2f", 10, 0
    format_int db "%.0f", 10, 0

section .text

global CMAIN

CMAIN:
    push ebp
    mov ebp, esp
    
    ; a)
    fld qword[num1]
    fld qword[num2]
    fcomi
    jl lower
    
    PRINT_STRING "greater"
    jmp done_a
    
lower:
    PRINT_STRING "lower"
    
done_a:
    fstp st0
    NEWLINE
    
    ; b)
    fld qword[num1]
    fsub qword[num2]
    fabs
    
    sub esp, 8
    fstp qword[esp]
    push format
    call printf
    add esp, 12
    
    
    ; c)
    fld qword[num1]
    fsub qword[num2]
    fabs
    frndint
    
    sub esp, 8
    fstp qword[esp]
    push format_int
    call printf
    add esp, 12
    
    xor eax, eax
    leave
    ret