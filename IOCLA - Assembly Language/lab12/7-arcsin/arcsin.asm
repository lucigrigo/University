%include "io.inc"

extern printf

section .data
    valoare_sin dq 0.9
    max    dq   1.57079632679
    min    dq   0.0
    eroare dq   0.0005

    med    dq   0.0
    format db   "Unghi gasit: %.20f", 10, 0

    sin    dq   0.0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging

repeat:
    ; med = (max + min) / 2
    push 2
    fld qword [max]
    fadd qword [min]
    fidiv dword [esp]
    fstp qword [med]
    add esp, 4
    
    ; TODO sin(med) - valoarea med este deja pe stiva
    fld qword[med]
    fsin
    
    ;push qword[med + 4]
    ;push qword[med]
    ;push format
    ;call printf
    ;add esp, 12

    ; TODO stocare rezultat in variabila sin
    fstp qword[sin]

    ; TODO comparatie cu valoarea cautata (valoare_sin)
    fld qword[sin]
    fld qword[valoare_sin]
    fcomip
    ja smaller

    ; TODO ajustare interval in functie de rezultatul comparatiei (min=med sau max=med)
    fld qword[med]
    fstp qword[max]
    fstp ST0
    jmp verif_err
    
smaller:
    fld qword[med]
    fstp qword[min]
    fstp ST0

    ; TODO verificare eroare (abs(valoare_sin-sin) < eroare)
verif_err:
    fld qword[valoare_sin]
    fsub qword[sin]
    fabs
    fld qword[eroare]
    ;fstp qword[valoare_sin]
    fcomip
    jb next_iter
    jmp done

    ; TODO loop daca eroarea este mai mare decat cea maxima

next_iter:
    jmp repeat
    
    ; TODO afisare rezultat. Valoarea trebuie sa fie aproximativ 0.123312275
done:
    push dword[med + 4]
    push dword[med]
    push format
    call printf
    add esp, 12

    xor eax, eax
    ret
