%include "io.inc"

; https://en.wikibooks.org/wiki/X86_Assembly/Arithmetic

section .data
    newline db 13, 10, 0
    num1 db 43
    num2 db 39
    num1_w dw 1349
    num2_w dw 9949
    num1_d dd 134932
    num2_d dd 994912
    print_mesaj dd 'Rezultatul este: 0x', 0

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    ; Multiplication for db
    mov al, byte [num1]
    mov bl, byte [num2]
    mul bl
    
    ; Print result in hexa
    PRINT_STRING [print_mesaj]
    PRINT_HEX 2, AX
    PRINT_STRING newline

   ; TODO: Implement multiplication for dw and dd data types.
    mov ax, word [num1_w]
    mov bx, word [num2_w]
    mul bx
    
    PRINT_STRING [print_mesaj]
    PRINT_HEX 2, DX
    PRINT_HEX 2, AX
    
    PRINT_STRING newline

    mov EAX, dword [num1_d]
    mov EBX, dword [num2_d]
    mul EBX
    
    PRINT_STRING [print_mesaj]
    PRINT_HEX 4, EDX
    PRINT_HEX 4, EAX
    PRINT_STRING newline

    leave
    ret
