%include "io.inc"

extern fgets
extern stdin
extern printf

section .data
    n            dd 7
    format_str   dd "Number: %d", 13, 10, 0
    prime_format dd "isPrime: %d", 13, 10, 0

section .text
global main

;TODO b: Implement stringToNumber
stringToNumber:

;TODO c.: Add missing code bits
isPrime:

loop:
    div ecx
    cmp edx, 0
    je not_prime
    inc ecx
    mov eax, [ebp+8]
    xor edx, edx
    cmp ecx, ebx
    jne loop
    
    jmp done
    
not_prime:
    jmp done
    
done:



CMAIN:
    push ebp
    mov ebp, esp

    ;TODO a.: allocate space on stack and call fgets

    ;TODO b.: call stringToNumber and print it using printf

    ;TODO c.: call isPrime and print result

    leave
    ret
