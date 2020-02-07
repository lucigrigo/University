%include "io.inc"

section .text
global CMAIN
CMAIN:
    ;cele doua multimi se gasesc in eax si ebx
    mov eax, 139 
    mov ebx, 169
    mov ecx, eax
    PRINT_DEC 4, eax ; afiseaza prima multime
    NEWLINE
    PRINT_DEC 4, ebx ; afiseaza cea de-a doua multime
    NEWLINE
    
    ;Prima multime:  {0, 1, 3, 7}
    ;A doua multime: {0, 3, 5, 7}

    ; TODO1: reuniunea a doua multimi
    OR ecx, ebx
    PRINT_STRING "Reuniunea este: "
    PRINT_DEC 4, ecx 
    NEWLINE ; ECX devine reuniunea: {0, 1, 3, 5, 7}

    ; TODO2: adaugarea unui element in multime
    mov ecx, eax
    OR ecx, 256
    OR ecx, 512
    PRINT_STRING "Dupa ce am adaugat 256 si 512 in prima multime, ea devine: "
    PRINT_DEC 4, ecx 
    NEWLINE ; ECX devine: {0, 1, 3, 5, 7, 8, 9}

    ; TODO3: intersectia a doua multimi
    mov ecx, eax
    AND ecx, ebx
    PRINT_STRING "Intersectia este: "
    PRINT_DEC 4, ecx 
    NEWLINE

    ; TODO4: complementul unei multimi
    mov ecx, eax
    NOT ecx
    PRINT_STRING "Complementul primei multimi: "
    PRINT_DEC 4, ecx 
    NEWLINE

    ; TODO5: eliminarea unui element
    mov ecx, eax
    AND ecx, 4294967294 ; il eliminam pe 0 din mutime
    PRINT_STRING "Dupa ce il eliminam pe 0 din prima multime, aceasta devine: "
    PRINT_DEC 4, ecx 
    NEWLINE

    ; TODO6: diferenta de multimi EAX-EBX
    mov ecx, eax
    XOR ecx, ebx
    AND ecx, eax
    PRINT_STRING "Diferenta dintre multimi este: "
    PRINT_DEC 4, ecx
    NEWLINE

    xor eax, eax
    ret
