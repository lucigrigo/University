%include "io.inc"

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    mov eax, 211    ; to be broken down into powers of 2
    mov ebx, 1      ; stores the current power

; TODO - print the powers of 2 that generate number stored in EAX
start:
    test eax, ebx
    jnz display
    
    shl ebx, 1
    cmp eax, ebx
    jge start
    
    jmp end
    
display:
    PRINT_DEC 4, ebx
    NEWLINE
    shl ebx, 1
    jmp start   
    
end:
    leave
    ret
