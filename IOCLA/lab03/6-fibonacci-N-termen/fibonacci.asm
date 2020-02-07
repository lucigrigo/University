%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    mov ecx, 7       ; vrem sa aflam al N-lea numar; N = 7
    ; TODO: calculati al N-lea numar fibonacci (f(0) = 0, f(1) = 1)
    dec ecx
    
    mov ebx, 0 ; begin
    mov eax, 1 ; middle     
    
    dec ecx
    
start:

    xchg ebx, eax
    add eax, ebx
    loop start
      
    add ebx, eax
    
    PRINT_DEC 4, ebx
    NEWLINE
    PRINT_STRING "Numarul cautat este: "
    PRINT_DEC 4, ebx  
    ret