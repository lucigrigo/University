%include "io.inc"

%define NUM 5

section .text
global CMAIN
CMAIN:
    mov ebp, esp

    ; TODO 1: replace every push by an equivalent sequence of commands
    
    ; pushing an array on the stack
    mov ecx, NUM
push_nums:
    ;push ecx
    sub esp, 4
    mov [esp], ecx
    loop push_nums

    ; pushing a string on the stack
    ;push 0
    mov eax, 0
    sub esp, 4
    mov [esp], eax
    ;push "mere"
    mov eax, "mere"
    sub esp, 4
    mov [esp], eax
    ;push "are "
    mov eax, "are "
    sub esp, 4
    mov [esp], eax
    ;push "Ana "
    mov eax, "Ana "
    sub esp, 4
    mov [esp], eax

    ; TODO 2: print the stack in "address: value" format in the range of [ESP:EBP]
    ; (from low addresses to high addresses, byte by byte)
    mov eax, esp
iter:
    PRINT_STRING "0x"
    PRINT_HEX 4, eax
    PRINT_STRING ": "
    PRINT_UDEC 1, [eax]
    NEWLINE
    inc eax
    cmp eax, ebp
    jl iter
    
    ; TODO 3: print the string byte by byte
    mov eax, esp
    xor edx, edx
iter2:
    PRINT_CHAR [eax]
    PRINT_CHAR " "
    inc eax
    inc edx
    cmp edx, 12
    jl iter2

    NEWLINE
    ; TODO 4: print the array element by element
iter3:
    PRINT_UDEC 4, [eax]
    PRINT_CHAR " "
    add eax, 4
    cmp eax, ebp
    jl iter3
    
    ; restore the previous value of the EBP (Base Pointer)
    mov esp, ebp

    ; exit without errors
    xor eax, eax
    ret
