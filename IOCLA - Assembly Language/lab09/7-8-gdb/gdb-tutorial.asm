extern gets
extern atoi
extern printf
global main

section .data
    usage_msg: db "Usage: %s index", 10, 0
    print_chr_format: db "%c", 10, 0

section .text
usage:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]
    push eax
    push usage_msg
    call printf

    leave
    ret
main:
    push ebp
    mov ebp, esp
    sub esp, 1024

    mov eax, [ebp + 8]
    cmp eax, 1
    jg ok
    mov eax, [ebp + 12]
    push dword [eax]
    call usage
    jmp not_found
ok:
    push esp
    call gets
    add esp, 4

    mov eax, [ebp + 12]
    push dword [eax + 4]
    call atoi
    add esp, 4

    mov edx, eax
    mov ebx, esp
    xor ecx, ecx
    xor eax, eax
for:
    mov al, [ebx + ecx]
    cmp ecx, edx
    je found
    test al, al
    je not_found
    inc ecx
    jmp for


found:
    push eax
    push print_chr_format
    call printf
not_found:
    leave
    ret

