%include "io.inc"

section .data
    array_1 db 27, 46, 55, 83, 84
    array_2 db 1, 4, 21, 26, 59, 92, 105
    array_output times 12 db 0

%define ARRAY_1_LEN 5
%define ARRAY_2_LEN 7
%define ARRAY_OUTPUT_LEN 12

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging

    mov eax, 0 ; counter used for array_1
    mov ebx, 0 ; counter used for array_2
    mov ecx, 0 ; counter used for the output array

merge_arrays:
    mov dl, byte [array_1 + eax]
    mov dh, byte [array_2 + ebx]
    cmp dl, dh
    jg array_2_lower
array_1_lower:
    ;mov byte [array_output + ecx], dl
    sub esp, 1
    mov [esp], dl
    inc eax
    inc ecx
    jmp verify_array_end
array_2_lower:
    ;mov byte [array_output + ecx], dh
    sub esp, 1
    mov [esp], dh
    inc ecx
    inc ebx

verify_array_end:
    cmp eax, ARRAY_1_LEN
    jge copy_array_2
    cmp ebx, ARRAY_2_LEN
    jge copy_array_1
    jmp merge_arrays

copy_array_1:
    mov dl, byte [array_1 + eax]
    ;mov byte [array_output + ecx], dl
    sub esp, 1
    mov [esp], dl
    inc ecx
    inc eax
    cmp eax, ARRAY_1_LEN
    jb copy_array_1
    jmp print_array
copy_array_2:
    mov dh, byte [array_2 + ebx]
    ;mov byte [array_output + ecx], dh
    sub esp, 1
    mov [esp], dh
    inc ecx
    inc ebx
    cmp ebx, ARRAY_2_LEN
    jb copy_array_2

print_array:
    PRINT_STRING "Array merged: "
    NEWLINE
    mov ecx, 0
print:
    ;PRINT_UDEC 1, [array_output + ecx]
    mov ebx, esp
    sub ebx, ecx
    PRINT_UDEC 1, [ebx + ARRAY_OUTPUT_LEN - 1]
    NEWLINE
    inc ecx
    cmp ecx, ARRAY_OUTPUT_LEN
    jb print

    mov esp, ebp
    xor eax, eax
    ret