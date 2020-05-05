%include "io.inc"

extern fgets
extern stdin
extern printf

section .data
    n            dd 7
    format_str   dd "Number: %d ", 13, 10, 0
    prime_format dd "isPrime: %d", 13, 10, 0

section .text
global main

;TODO b: Implement stringToNumber
stringToNumber:
    push ebp
    mov ebp, esp
    
    mov ebx, [ebp + 8]
    xor ecx, ecx
    xor eax, eax
convert:
    cmp byte[ebx + ecx], 0x00
    je done_convert
    cmp byte[ebx + ecx], 10
    je done_convert
    xor edx, edx
    mov dl, byte[ebx + ecx]
    sub dl, 48
    push ebx
    push edx
    push ecx
    mov edx, 10
    mul edx
    pop ecx
    pop edx
    pop ebx
    add eax, edx
    
    inc ecx
    jmp convert
    
done_convert:
    mov dword[ebp + 8], eax
    leave
    ret

;TODO c.: Add missing code bits
isPrime:
    push ebp
    mov ebp, esp

    mov eax, dword[ebp + 8]
    mov ebx, eax
    mov ecx, 2
    xor edx, edx
    ;mov dword[ebp + 8], 1
    mov dword[ebp + 12], 1
loop:
    ;push ebx
    div ecx
    ;pop ebx
    cmp edx, 0
    je not_prime
    inc ecx
    mov eax, dword [ebp + 8]
    xor edx, edx
    cmp ecx, ebx
    jne loop
    
    jmp done
    
not_prime:
    mov dword[ebp + 12], 0
    jmp done
    
done:
    leave
    ret


CMAIN:
    push ebp
    mov ebp, esp

    ;TODO a.: allocate space on stack and call fgets
    
    push dword[stdin]
    push dword[n]
    push eax
    call fgets
    add esp, 12
    
    ;TODO b.: call stringToNumber and print it using printf
    push eax
    call stringToNumber
    pop eax
    
    push eax
    push dword format_str
    call printf
    add esp, 8
    
    ;TODO c.: call isPrime and print result
    push ebx
    push eax
    call isPrime
    pop eax
    pop ebx
    
    push ebx
    push dword prime_format
    call printf
    add esp, 8
end:
    leave
    ret
