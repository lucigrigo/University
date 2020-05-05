%include "io.inc"
 
section .text
global CMAIN
CMAIN:
    mov eax, 7          ; incarca in registrul eax valoarea 7
    mov ebx, 8          ; incarca in registrul ebx valoarea 8
    add eax, ebx        ; aduna valoarea ce se afla in registrul eax
                        ; cu valoarea ce se afla in registrul ebx si
                        ; stocheaza rezultatul in eax
    PRINT_UDEC 4, eax   ; printeaza valoarea din registrul eax
