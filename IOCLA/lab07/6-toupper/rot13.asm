%include "io.inc"
extern printf

section .data
    before_format db "before %s", 13, 10, 0
    after_format db "after %s", 13, 10, 0
    mystring db "ana", 0, "are", 0, "mere", 0
    len dd 12

section .text
global CMAIN

toupper:
    push ebp
    mov ebp, esp
    
    mov eax, mystring
    mov ecx, [len]
    
test_one_byte:
    mov bl, byte [eax]
    cmp ecx, 0
    jle out
    
    cmp bl, 0
    jne tag
    mov byte [eax], ' '
    jmp endif2
    
tag:    
    cmp bl, 'a'
    jb endif
    cmp bl, 'z'
    ja endif
    add bl, 13
    cmp bl, 'z'
    jbe end
    sub bl, 26
end:
    mov byte [eax], bl

endif:
    
    cmp bl, 'A'
    jb endif2
    cmp bl, 'Z'
    ja endif2 
    add bl, 13
    cmp bl, 'Z'
    jbe end2
    sub bl, 26 
    
end2:
    mov byte [eax], bl
    
endif2:
    inc eax
    dec ecx
    jmp test_one_byte
out:   
    leave
    ret

CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp

    push mystring
    push before_format
    call printf
    add esp, 8

    push mystring
    call toupper
    add esp, 4

    push mystring
    push after_format
    call printf
    add esp, 8

    leave
    ret
