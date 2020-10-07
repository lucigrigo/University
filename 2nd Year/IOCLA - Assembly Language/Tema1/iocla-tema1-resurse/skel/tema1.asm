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
    index dd 0
    var dw 0
    instructionLength dd 0
    indexTemp dd 0
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
    
    ; Calculez lungimea inputului (a instructiunii)
    mov eax, [root]
    mov ebx, [eax]
    mov ecx, 0
computeInstructionLength:
    mov edx, [instructionLength]
    add edx, 32    
    mov [instructionLength], edx
    cmp dword [ebx + edx], 0x00
    jne computeInstructionLength
    
    ; Incep calcularea rezultatului expresiei (de la finalul inputului)
    mov ecx, [instructionLength]
    sub ecx, 32
computeRPNResult:
    mov [var], ebx
    add [var], ecx
    mov eax, [var]
    
    ; verificam daca elementul curent este un operator
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
    mov ebx, 10
convert:
    ; il convertim caracter cu caracter
    xor ecx, ecx    
    mov esi, [index]
    mov cl, byte[edx + esi]
    cmp cl, 45
    jne skipSign
    mov byte[isNegativeNumber], 1
    inc byte[index]
    jmp convert
skipSign:
    ; cazul in care numarul este pozitiv
    sub cl, 48 
    add eax, ecx
    inc byte[index]
    mov esi, [index]
    cmp byte[edx + esi], 0x00
    je convertNegative
    mov ebx, edx
    mov edx, 10
    mul edx
    mov edx, ebx
    jmp convert
    ; cazul in care numarul este negativ
convertNegative:
    cmp byte[isNegativeNumber], 1
    jne endConvert
    NEG eax
    mov byte[isNegativeNumber], 0
    ; la final, il punem pe stiva
endConvert:
    push eax
    mov ecx, [indexTemp]
    mov ebx, edi
    jmp check
    ; aplica operatia de scadere
substraction:
    ; intai verifica ca nu s-a ajuns aici cu un numar negativ
    cmp byte[eax + 1], 0x00
    mov byte[isNegativeNumber], 1
    jne initConvert
    pop eax
    pop edx
    sub eax, edx
    push eax
    jmp check
    ; aplica operatia de adunare
addition:
    pop eax
    pop edx
    add eax, edx
    push eax
    jmp check
    ; aplica operatia de inmultire
multiplication:
    pop eax
    pop edx
    imul edx
    push eax
    jmp check
    ; aplica operatia de impartire
division:
    mov [indexTemp], ebx
    pop eax
    cdq
    pop ebx
    idiv ebx
    mov ebx, [indexTemp]
    push eax
    jmp check
    ; verificam daca am terminat de executat operatiile din input
check:
    sub ecx, 32
    cmp ecx, 0
    jge computeRPNResult
    
    ; valoarea ramasa pe stiva este rezultatul operatiilor
    pop eax
    PRINT_DEC 4, eax
    NEWLINE
    
    ; NU MODIFICATI
    ; Se elibereaza memoria alocata pentru arbore

    push dword [root]
    call freeAST
    
    xor eax, eax
    leave
    ret