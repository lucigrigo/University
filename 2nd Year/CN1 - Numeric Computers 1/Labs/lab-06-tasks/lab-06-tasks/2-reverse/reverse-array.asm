%include "io.inc"

section .data

%define ARRAY_LEN 7

    input dd 122, 184, 199, 242, 263, 845, 911
    output times ARRAY_LEN dd 0

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    ; TODO push the elements of the array on the stack
    mov ecx, ARRAY_LEN
push_elem:
    push word [input + ecx * 4]
    dec ecx
    cmp ecx, 0
    jge push_elem
    
    ; TODO retrieve the elements (pop) from the stack into the output array
    mov ecx, ARRAY_LEN - 1
pop_elem:
    pop word[output + ecx * 4]
    dec ecx
    cmp ecx, 0
    jge pop_elem
    
    PRINT_STRING "Reversed array:"
    NEWLINE
    xor ecx, ecx
print_array:
    PRINT_UDEC 4, [output + 4 * ecx]
    NEWLINE
    inc ecx
    cmp ecx, ARRAY_LEN
    jb print_array

    xor eax, eax
    mov esp, ebp
    leave
    ret
