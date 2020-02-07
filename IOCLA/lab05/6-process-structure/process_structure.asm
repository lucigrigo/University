%include "io.inc"

struc stud_struct
    name: resb 32
    surname: resb 32
    age: resb 1
    group: resb 8
    gender: resb 1
    birth_year: resw 1
    id: resb 16
endstruc

section .data

sample_student:
    istruc stud_struct
        at name, db 'Andrei', 0
        at surname, db 'Voinea', 0
        at age, db 21
        at group, db '321CA', 0
        at gender, db 1
        at birth_year, dw 1994
        at id, db 0
    iend

print_format db "ID:", 0

section .text
global CMAIN

CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp

    ; TODO: store in a register the address of the sample_student struct
    
    ; TODO: copy the first 3 bytes from the name field to id using movsb
    mov ecx, 3
    mov esi, sample_student + name
    mov edi, sample_student + id
    rep movsb
    ; TODO: copy the first 3 bytes from the surname field to id using movsb
    mov ecx, 3
    mov esi, sample_student + surname
    rep movsb
    ; TODO: insert `-`
    xor eax, eax
    mov al, '-'
    stosb
    ; TODO: copy the bytes from field group to id using movsb
    mov ecx, 5
    mov esi, sample_student + group
    rep movsb
    
    mov byte [sample_student + id + 13], '\0'
    
    ; print the new ID added
    PRINT_STRING print_format
    PRINT_STRING [sample_student + id]
    
    leave
    ret