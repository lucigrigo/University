%include "io.inc"

; https://en.wikibooks.org/wiki/X86_Assembly/Arithmetic

section .data
    string_quotient db "Quotient: ", 0
    string_remainder db "Remainder: ", 0
    dividend1 db 91
    divisor1 db 27
    dividend2 dd 67254
    divisor2 dw 1349
    dividend3 dq 69094148
    divisor3 dd 87621

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    xor eax, eax

    mov al, byte [dividend1]
    mov bl, byte [divisor1]
    div bl
    
    PRINT_STRING string_quotient
    PRINT_UDEC 1, AL
    NEWLINE
    PRINT_STRING string_remainder
    PRINT_UDEC 1, AH
    NEWLINE
    
    ; TODO: Calculate quotient and remainder for 67254 / 1349.
    xor eax, eax
    xor ebx, ebx
    xor edx, edx
    
    mov ax, word [dividend2]
    mov dx, word [dividend2 + 2]
    mov bx, word [divisor2]
    div bx
    
    PRINT_STRING string_quotient
    PRINT_UDEC 2, AX
    NEWLINE
    PRINT_STRING string_remainder
    PRINT_UDEC 2, DX
    NEWLINE

    ; TODO: Calculate quotient and remainder for 69094148 / 87621.
    xor eax, eax
    xor ebx, ebx
    xor edx, edx
    mov eax, dword[dividend3]
    mov edx, dword[dividend3 + 4]
    mov ebx, dword[divisor3]
    div ebx
    
    PRINT_STRING string_quotient
    PRINT_UDEC 4, EAX
    NEWLINE
    PRINT_STRING string_remainder
    PRINT_UDEC 4, EDX
    NEWLINE
    
   
    leave
    ret
