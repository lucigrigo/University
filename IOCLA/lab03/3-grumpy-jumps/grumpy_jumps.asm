%include "io.inc"

section .data
    wrong: db 'Not today, son.',0
    right: db 'Well done!',0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    mov eax, 0x2 ; TODO3.1: modify eax register
    mov ebx, 0x3;  TODO3.1: modify ebx register
    mov ecx, 0x5        ; hardcoded; DO NOT change
    cmp eax, ebx
    jns bad
    cmp ecx, ebx
    jb bad
    add eax, ebx
    xor eax, ecx
    jnz bad
good:
    PRINT_STRING right
    NEWLINE
    jmp end
bad:
    PRINT_STRING wrong
    NEWLINE
end:
    ret
