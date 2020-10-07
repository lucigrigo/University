%include "io.inc"

section .data
    vector dq -86.601, 12.11, 84.4483, -31.1, -76.606, 91.2086, -18.12, -70.73, -0.09922
    n      dd ($-vector)/8
    format db "Valoarea maxima: %f", 10, 0
    max    dq -1000000.0

section .text
global CMAIN
CMAIN:

    mov ecx, dword [n]
    mov eax, vector

repeat:
    cmp ecx, 0
    je done

    fld qword [eax]
    fld qword [max]
    fcomip    ; compara cele doua valori adaugate pe stiva

    ; In acest punct, avem pe stiva FPU doar valoarea din vector (fcomip extrage prima valoare), iar flag-urile din EFLAGS
    ; sunt setate conform comparației.
    jb bigger
    jmp next
  
    ; TODO Verifica rezultatul comparatiei folosind o instructiune conditionala.

    ; TODO Daca valoarea este mai mare decat cea maxima, extrage valoarea de pe stiva in variabila max (hint: fstp).
bigger:
    fstp qword[max]
    fstp ST0
    jmp next
    
    ; TODO Daca valoarea este mai mica decat cea maxima, doar elibereaza stiva (instructiunea fstp ST0).
smaller:
    fstp ST0
    fstp ST0
    
next:
    add eax, 8
    dec ecx
    jmp repeat


done:

    ; TODO Afiseaza rezultatul
    ; TODO Stocheaza valoarea maxima pe stiva. Are 8 octeti, deci sunt necesare doua push-uri.
    push dword[max + 4]
    push dword[max]
    push format
    call printf
    add esp, 12

    xor eax, eax
    ret
