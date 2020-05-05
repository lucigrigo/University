%include "io.inc"
section .data
    N dd 9 ; compute the sum of the first N fibonacci numbers
    
section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    mov ecx, [N]
    xor edx, edx 
    dec ecx
    
    mov ebx, 0 ; begin
    mov eax, 1 ; middle  
    
    add edx, eax
     
    dec ecx
  
start:

    xchg ebx, eax
    add eax, ebx
    add edx, eax    
    
    loop start
    ; TODO: calculate the sum of first N fibonacci numbers
    ;       (f(0) = 0, f(1) = 1)
    ;       store the sum in eax
    ;       use loop instruction 

    
    PRINT_STRING "Sum first "
    PRINT_DEC 4, [N]
    PRINT_STRING " fibo is "
    PRINT_UDEC 4, eDx

    leave
    ret
