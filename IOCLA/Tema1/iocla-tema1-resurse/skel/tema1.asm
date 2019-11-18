; Introducere in Organizarea Calculatoarelor si Limbaj de Asamblare
; Tema 1 - Prefix AST
; Grigore Lucian-Florin
; 324CD
; Facultatea de Automatica si Calculatoare
; Universitatea Politehnica, Bucuresti

%include "io.inc"

extern getAST
extern freeAST

section .bss
    ; La aceasta adresa, scheletul stocheaza radacina arborelui
    root: resd 1
    
section .data
    ;instructionArray: times 200000 db 0
    ;instructionArraySize dw 0
    index dd 0
    var dw 0
    instructionLength dd 0
    ten dd 10
    singleByte db 0
    indexTemp dd 0
    i dd 0
    isNegativeNumber db 0

section .text
global main

main:
    ; NU MODIFICATI
    push ebp
    mov ebp, esp
    
    ; Se citeste arborele si se scrie la adresa indicata mai sus
    call getAST
    mov [root], eax
    
    ; Implementati rezolvarea aici:

    mov eax, [root]
    mov ebx, [eax]
    mov ecx, 0
computeInstructionLength:
    mov edx, [instructionLength]
    add edx, 32    
    mov [instructionLength], edx
    cmp dword [ebx + edx], 0x00
    jne computeInstructionLength
    
    mov ecx, [instructionLength]
    sub ecx, 32
computeRPNResult:
    mov [var], ebx
    add [var], ecx
    mov eax, [var]
    
    ;PRINT_STRING [ebx + ecx]
    ;NEWLINE
    ; verificam daca este un operator
    cmp byte[eax], "-"
    je substraction
    cmp byte[eax], "+"
    je addition
    cmp byte[eax], "*"
    je multiplication
    cmp byte[eax], "/"
    je division
    
    ; in acest moment stim sigur ca avem de-a face cu un numar
    ; si incercam sa il convertim in decimal
    
initConvert:
    mov byte[index], 0
    xor edx, edx
    mov edx, eax
    mov [indexTemp], ecx
    xor eax, eax
    mov edi, ebx
    mov ebx, [ten]
convert:
    xor ecx, ecx    
    mov esi, [index]
    mov cl, byte[edx + esi]
    ;PRINT_STRING [edx]
    ;NEWLINE
    cmp cl, 45
    jne skipSign
    ;PRINT_STRING "YEYU"
    mov byte [isNegativeNumber], 1
    inc byte[index]
    jmp convert
    
skipSign:
    sub cl, 48 
    add eax, ecx
    
    inc byte[index]
    mov esi, [index]

    cmp byte[edx + esi], 0x00
    je endConvert
    mov ebx, edx
    mov edx, [ten]
    mul edx
    mov edx, ebx
    jmp convert
    
endConvert:
    cmp byte [isNegativeNumber], 1
    jne positiveNumber
    ;PRINT_DEC 4, eax
    ;NEWLINE
    ;PRINT_STRING "AICI"
    NEG eax
    mov byte[isNegativeNumber], 0
    
positiveNumber:
;PRINT_DEC 4, EAX
;NEWLINE
    push eax
    mov ecx, [indexTemp]
    mov ebx, edi
    jmp check
    
substraction:
    cmp byte[eax + 1], 0x00
    mov byte[isNegativeNumber], 1
    jne initConvert
    pop eax
    pop edx
    sub eax, edx
    push eax
    jmp check
    
addition:
    pop eax
    pop edx
    add eax, edx
    push eax
    jmp check
    
multiplication:
    pop eax
    pop edx
    imul edx
    push eax
    jmp check
    
division:
    mov [indexTemp], ebx
    pop eax
    cdq
    pop ebx
    idiv ebx
    mov ebx, [indexTemp]
    push eax
    jmp check

check:
    sub ecx, 32
    cmp ecx, 0
    jge computeRPNResult
    
    pop eax
    PRINT_DEC 4, eax
    NEWLINE
    
    ; NU MODIFICATI
    ; Se elibereaza memoria alocata pentru arbore
end:
    ;mov esp, ebp

    push dword [root]
    call freeAST
    
    xor eax, eax
    leave
    ret