extern rand
extern time
extern srand
extern scanf
extern printf
extern puts


section .data
    uint_format    db "%zu", 0
    uint_format_newline    db "%zu", 10, 0
    msg    db "Insert number: ", 0
    is_smaller_string db "Numarul introdus este mai mic", 0
    is_larger_string db "Numarul introdus este mai mare", 0


section .bss
    num resd 1


section .text


; TODO c: Create read_cmp() function.



global main
main:
    push ebp
    mov ebp, esp


    ; TODO a: Call srand(time(0)) and then rand() and store return value modulo 100 in num.



    ; Debug only: Print value of num to check it was properly initialized.
    push dword [num]
    push uint_format_newline
    call printf
    add esp, 8

    ; Comment this out when doing TODO b. Uncomment it when doing TODO c and d.
    jmp make_call
    
    ; TODO b: Read numbers from keyboard in an infinite loop.



make_call:
    
    ; TODO d:



    ; Return 0.
    xor eax, eax
    leave
    ret
