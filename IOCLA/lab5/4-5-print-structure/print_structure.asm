%include "io.inc"

struc stud_struct
    name: resb 32
    surname: resb 32
    age: resb 1
    group: resb 8
    gender: resb 1
    birth_year: resw 1
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
    iend

string_name db "Name: ", 0
string_surname db "Surname: ", 0
string_age db "Age: ", 0
string_group db "Group: ", 0
string_gender db "Gender: ", 0
string_year db "Birth year: ", 0

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    ; TODO: Update name, surname, birth_year, gender and age such that:
    ; birth_year is 1993
    ; age is 22
    ; group is '323CA'
    
    mov eax, 22
    mov [sample_student + age], eax
    ;xor eax, eax
    
    mov eax, 1993
    mov [sample_student + birth_year], eax
    ;xor eax, eax

    mov eax, '323CA'
    mov [sample_student + group], eax 
    ;xor eax, eax

    PRINT_STRING string_name
    PRINT_STRING sample_student + name
    NEWLINE

    PRINT_STRING string_surname
    PRINT_STRING sample_student + surname
    NEWLINE
    mov al, byte [sample_student + age]
    PRINT_STRING string_age
    PRINT_UDEC 1, al
    NEWLINE
    
    PRINT_STRING string_group
    PRINT_STRING sample_student + group
    NEWLINE
    mov al, byte [sample_student + gender]
    PRINT_STRING string_gender
    PRINT_UDEC 1, al
    NEWLINE
    mov ax, [sample_student + birth_year]
    PRINT_STRING string_year
    PRINT_UDEC 2, ax
    NEWLINE

    leave
    ret
