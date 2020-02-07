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
    sub esp, 4
    mov [esp], ecx
    loop push_nums

    ; pushing a string on the stack
    sub esp, 4
    mov [esp], dword 0
    sub esp, 4
    mov [esp], dword "mere"
    sub esp, 4
    mov [esp], dword "are "
    sub esp, 4
    mov [esp], dword "Ana "

    ; TODO 2: print the stack in "address: value" format in the range of [ESP:EBP]
    ; (from low addresses to high addresses, byte by byte)
    mov ebx, esp
    
print_stack:
    PRINT_STRING "0x"
    PRINT_HEX 4, ebx
    PRINT_STRING ": "
    PRINT_DEC 1, [ebx]
    NEWLINE
    inc ebx
    cmp ebx, ebp
    jne print_stack
    
    ; TODO 3: print the string byte by byte
    mov ebx, esp
    mov ecx, 12
    
print_str:
    PRINT_CHAR [ebx]
    inc ebx
    loop print_str
    NEWLINE
    
    ; TODO 4: print the array element by element
    mov ebx, ebp
    sub ebx, 20
    mov ecx, 5
    
print_arr:
    PRINT_DEC 4, [ebx]
    PRINT_STRING " "
    add ebx, 4
    cmp ebx, ebp
    jl print_arr
    
    ; restore the previous value of the EBP (Base Pointer)
    mov esp, ebp

    ; exit without errors
    xor eax, eax
    ret