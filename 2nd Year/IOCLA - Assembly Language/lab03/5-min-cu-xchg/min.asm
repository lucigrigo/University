%include "io.inc"

section .text
global CMAIN
CMAIN:
    ;cele doua numere se gasesc in eax si ebx
    mov eax, 4
    mov ebx, 5
    ; TODO: aflati minimul
    
    cmp eax, ebx
    jb end
          
    xchg eax, ebx     
    
end:    
    PRINT_DEC 4, eax ; afiseaza minimul
    NEWLINE

    ret