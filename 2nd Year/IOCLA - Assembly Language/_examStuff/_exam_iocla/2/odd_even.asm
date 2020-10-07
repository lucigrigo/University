extern puts
extern printf


section .rodata
    arr1 dd 9, 11, 13, 15, 16, 18, 20
    len1 equ 7
    arr2 dd 11, 22, 33, 44, 55, 66, 77, 88, 99, 101
    len2 equ 10
    arr3 dw 2, 4, 6, 8, 9, 11
    len3 equ 6
    odd_fmt db "number of odd numbers in array: %u", 10, 0
    even_fmt db "number of even numbers in array: %u", 10, 0


section .text
global main


num_bits:
    push ebp
    mov ebp, esp

    ; TODO a: Implement num_bits(array, len, odd) to return the
    ; number of odd/even numbers in array of len integer (4 bytes) elements.
    mov esi, dword[ebp + 12] ; array size
    mov edi, dword[ebp + 8] ; array
    mov ebx, dword[ebp + 16] ; isOdd
    
    xor edx, edx
    inc edx
    cmp ebx, 1
    je start_iter
    
    xor edx, edx
    
start_iter:
    xor eax, eax
    xor ecx, ecx
test_oddness:
    mov ebx, dword[edi + 4 * ecx]
    shl ebx, 31
    shr ebx, 31
    cmp ebx, edx
    jne next_iter
    
    inc eax
next_iter:    
    inc ecx
    cmp ecx, esi
    jne test_oddness
    
    leave
    ret


num_odd:
    push ebp
    mov ebp, esp

    ; TODO b: Implement num_odd(array, len) as wrapper over num_bits.
    mov esi, dword[ebp + 8] ; array
    mov edi, dword[ebp + 12] ; array size

    push 1
    push edi
    push esi    
    call num_bits
    add esp, 12
    
    leave
    ret


num_even:
    push ebp
    mov ebp, esp

    ; TODO b: Implement num_even(array, len) as wrapper over num_bits.
    mov esi, dword[ebp + 8] ; array
    mov edi, dword[ebp + 12] ; array size

    push 0
    push edi
    push esi    
    call num_bits
    add esp, 12

    leave
    ret


num_bits_size:
    push ebp
    mov ebp, esp

    ; TODO c: Implement num_bits_size(array, size, len, odd) to return the
    ; number of odd/even numbers in array of len elements of size.
    mov esi, dword[ebp + 8] ; array
    mov ebx, dword[ebp + 12] ; size of element
    mov edi, dword[ebp + 16] ; array length
    mov edx, dword[ebp + 20] ; isOdd variable
    
    cmp edx, 1
    jne start_iter_c
    
    xor edx, edx
start_iter_c:
    
    xor eax, eax
    xor ecx, ecx    
iterate_c:
    push ebx
    push eax
    xor eax, eax
    mov eax, ecx
    mul ebx
    mov ebx, eax
    pop eax
    
    mov edx, dword[esi + ebx]
    shl edx, 31
    shr edx, 31
    cmp edx, 1
    jne next_iter_c
    
    inc eax
    
next_iter_c:
    pop ebx
    inc ecx
    cmp ecx, edi
    jne iterate_c
    
    
    leave
    ret


main:
    push ebp
    mov ebp, esp

    push dword 1
    push dword len2
    push dword arr2
    call num_bits
    add esp, 12

    push eax
    push odd_fmt
    call printf
    add esp, 8

    push dword len1
    push dword arr1
    call num_odd
    add esp, 8

    push eax
    push odd_fmt
    call printf
    add esp, 8

    push dword len1
    push dword arr1
    call num_even
    add esp, 8

    push eax
    push even_fmt
    call printf
    add esp, 8

    push dword 1
    push dword len3
    push dword 2
    push dword arr3
    call num_bits_size
    add esp, 16

    push eax
    push odd_fmt
    call printf
    add esp, 8

    ; Return 0.
    xor eax, eax
    leave
    ret
