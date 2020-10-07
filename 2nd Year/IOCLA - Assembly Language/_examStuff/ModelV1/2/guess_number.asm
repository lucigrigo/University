extern rand
extern time
extern srand
extern scanf
extern printf
extern puts


section .data
    uint_format    db "%d", 0
    uint_format_newline    db "%d", 10, 0
    msg    db "Insert number: ", 0
    is_smaller_string db "Numarul introdus este mai mic", 10, 0
    is_larger_string db "Numarul introdus este mai mare", 10, 0
    is_equal_string db "Numarul introdus este corect!", 10, 0


section .bss
    num resd 1
    nr_in resd 1

section .text


; TODO c: Create read_cmp() function.
read_cmp:
    push ebp
    mov ebp, esp
    
    mov ebx, [ebp + 8]
    cmp ebx, [num]
    je number_equal
    jl number_less
    
    ; number_greater
    push dword is_larger_string
    call printf
    add esp, 4
    
    mov dword [ebp + 12], 0
    jmp end_func
    
number_less:
    push dword is_smaller_string
    call printf
    add esp, 4
    
    mov dword [ebp + 12], 0
    jmp end_func
    
number_equal:
    push dword is_equal_string
    call printf
    add esp, 4
    
    mov dword [ebp + 12], 1
    
end_func:
    leave
    ret


global main
main:
    push ebp
    mov ebp, esp

    ; TODO a: Call srand(time(0)) and then rand() and store return value modulo 100 in num.
    push eax
    push 0
    call time
    push eax
    call srand
    call rand
    
    xor edx, edx
    mov ebx, 100
    div ebx
    
    mov [num], edx
   
    ; Debug only: Print value of num to check it was properly initialized.
    push dword [num]
    push uint_format_newline
    call printf
    add esp, 8

    ; Comment this out when doing TODO b. Uncomment it when doing TODO c and d.
    ;jmp make_call
    
    ; TODO b: Read numbers from keyboard in an infinite loop.
read_input:
    push dword msg
    call printf
    add esp, 4
    
    push nr_in
    push uint_format
    call scanf
    add esp, 8
    
    mov eax, [nr_in]
    push eax
    ;jmp read_input

make_call:
    call read_cmp
    
    ; TODO d:
    cmp dword[esp + 4], 1
    je number_found
    jmp read_input

number_found:
    ; Return 0.
    xor eax, eax
    leave
    ret
