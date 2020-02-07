%include "io.inc"
extern puts

section .data
    msg db 'Hello, world!', 10, 0

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    push msg
    call puts
    add esp, 4

    leave
    ret
