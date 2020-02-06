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
    mov ecx, 3

    ; TODO: store in a register the address of the sample_student struct
    mov eax, [sample_student]

    ; TODO: copy the first 3 bytes from the name field to id using movsb
    cld
    ;mov edx, byte [eax + id]
    ;mov esi, [eax + 8 * 1]
    ;rep movsb
    ;mov ecx, 3
    ;mov byte [eax + 40 + 16], [sample_student]
    

    ; TODO: copy the first 3 bytes from the surname field to id using movsb
   ; mov esi, [sample_student + surname]
    ;rep movsb
    ;mov ecx, 3

    ; TODO: insert `-`
    ;mov byte [sample_student + id + 5], '-'
    ;mov byte [sample_student + id + 6], '\0'

    ; TODO: copy the bytes from field group to id using movsb
    ;lmov esi, [sample_student + group]
    ;rep movsb

    ; print the new ID added
    PRINT_STRING print_format
    PRINT_STRING [sample_student + id]
    
    leave
    ret