#lang racket
; ignorați următoarele linii de cod.
(define show-defaults 2) ; câte exerciții la care s-au întors rezultate default să fie arătate detaliat
(define count-magic 0)
(define (magic-number) (set! count-magic (+ count-magic 1)) 42)
(define (magic-segment) (set! count-magic (+ count-magic 1)) (cons '(2 . 2)  '(6 . 7)))
(define (number->list num) (map (lambda (c) (- (char->integer c) (char->integer #\0))) (string->list (number->string num))))
(define (sum numbers) (foldr + 0 numbers))
(define (get-start-point x) (set! count-magic (+ count-magic 1)) (car x))
(define (get-end-point x) (set! count-magic (+ count-magic 1)) (cdr x))
(define prepend #f) (define name-ex '(testul . testele)) ; variante: '(exercițiul . exercițiile) sau '(testul . testele) sau '(task . taskurile)
(define default-results '(your-code-here ())) ; ce rezultate default sunt întoarse în exerciții
(define : 'separator) (define punct 'string) (define puncte 'string) (define BONUS 'string) (define total 0) (define all '()) (define n-ex 0) (define p-ex 0) (define defaults '())
(define (ex n sep p . s) (set! n-ex n) (set! p-ex p) (set! all (cons (list n p) all))) (define exercițiul ex) (define (p L) (map (λ (e) (display e) (display " ")) L) (newline))
(define (check-exp given expected) (check-exp-part "" 1 given expected)) (define (check-exp-part part percent given expected) (if (not (equal? given expected)) (and
                                                                                                                                                                 (when (member given default-results) (set! defaults (cons (if (< percent 1) (cons n-ex part) n-ex) defaults))) (when (or (not (member given default-results))
                                                                                                                                                                                                                                                                                          (<= (length defaults) show-defaults)) (p `(NU: la ,(car name-ex) ,(if (< percent 1) (cons n-ex part) n-ex) rezultatul ,given diferă de cel așteptat: ,expected))))
                                                                                                                                  (let ((pts (* p-ex percent))) (and (if prepend (printf "+~v: " pts) (printf "OK: "))
                                                                                                                                                                     (p `(,(car name-ex) ,(if (< percent 1) (cons n-ex part) n-ex) trecut + ,pts ,(if (= pts 1) 'punct 'puncte))) (set! total (+ total pts))))))(define (sumar) (when (and (not (null? defaults)) (< show-defaults (length defaults))) (p `(... rezultatul implicit dat la ,(cdr name-ex) ,(reverse defaults)))) (p `(total: ,total puncte)))
(define (mark-helper) (printf "----------~nEx  puncte    Total până aici~n") (foldr (λ (e-p t) (p `(,(car e-p) : ,(cadr e-p) puncte. total 1 - ,(car e-p) : ,(+ t (cadr e-p)))) (+ t (cadr e-p))) 0 all))


;; Acest laborator are ca scop familiarizarea cu legările
;; din Racket și restul limbajelor din familia LISP.

;; Cel mai important scop al acestui laborator este să vă arate cum puteți
;; face codul lizibil, țineți minte asta când rezolvați, dacă ați
;; folosit let-uri dar codul încă e greu de înțeles probabil
;; e timpul să regândiți logica exercițiului.

;; Abilitatea de a scrie cod lizibil este critică pentru un programator și vă
;; va influența major cariera. Nu vă demoralizați dacă încă nu sunteți pricepuți,
;; nu există o rețeță universală, această abilitate se dezvoltă
;; de-a lungul anilor de scris cod zilnic.


(exercițiul 1 : 1 puncte)
;; Funcția compute-square-area primește ca argument o funcție
;; ce returnează un număr, reprezentând latura unui pătrat;
;; compute-square-area trebuie să calculeze aria acelui pătrat.
;; Atenție: Aveți voie să aplicați get-length o singură dată.
;;          Nu puteți folosi `exp`/`expt`
(define (compute-square-area get-length)
  'your-code-here)

(let ([num-of-calls ((lambda () (compute-square-area magic-number) count-magic))])
  (check-exp-part 'a (/ 1. 4) num-of-calls 1)
  (when (= num-of-calls 1)
        (check-exp-part 'b (/ 1. 4) (compute-square-area (lambda () 3932)) 15460624)
        (check-exp-part 'c (/ 1. 4) (compute-square-area (lambda () 2788)) 7772944)
        (check-exp-part 'd (/ 1. 4) (compute-square-area (lambda () 198.2522)) 39303.93480483999)))
(set! count-magic 0)

(exercițiul 2 : 1 puncte)
;; Funcția compute-length primește ca argumente 3 funcții:
;;  - get-line-segment => întoarce un segment de dreaptă.
;;  - get-start-point => primește un segment de dreaptă și
;;                       întoarce punctul din care segmentul începe.
;;  - get-end-point => primește un segment de dreaptă și
;;                       întoarce punctul în care segmentul se termină.
;;
;; Un punct este reprezentat printr-o pereche de numere.
;; Un segment de dreaptă este reprezentat printr-o pereche de puncte.
;;
;; compute-length trebuie să calculeze lungimea segmentului de dreaptă.
;; (distanța dintre punctul de început și punctul de sfârșit)
;; Atenție: Fiecare funcție primită drept argument trebuie aplicată o singură dată.
(define (compute-length get-line-segment get-start-point get-end-point)
  'your-code-here)


(let ([num-of-calls ((lambda () (compute-length magic-segment get-start-point get-end-point) count-magic))])
  (check-exp-part 'a (/ 1. 5) num-of-calls 3)
  (when (= num-of-calls 3)
    (let ([fn-binding (lambda (x) (compute-length (lambda () x) get-start-point get-end-point))])
      (check-exp-part 'b (/ 1. 5) (fn-binding (cons '(9 . 12)  '(12 . 16))) 5)
      (check-exp-part 'c (/ 1. 5) (fn-binding (cons '(10 . 10)  '(94 . 197))) 205)
      (check-exp-part 'd (/ 1. 5) (fn-binding (cons '(23 . 54)  '(7632 . 5457))) 9332.164272021791)
      (check-exp-part 'e (/ 1. 5) (fn-binding (cons '(658 . 665)  '(32343 . 31246))) 44035.63086864999)
    )))
(set! count-magic 0)

(exercițiul 3 : 1 puncte)
;; Definiți funcția distance care calculează distanța
;; dintre două puncte bazându-se pe funcția compute-length.
;; Identificați închiderea funcțională și arătați-o
;; asistentului pentru a vă puncta acest exercițiu.
(define (distance p1 p2)
  'your-code-here)

(check-exp-part 'a 1 (distance '(9 . 12)  '(12 . 16)) 5)

(exercițiul 4 : 1 puncte)
;; Fie f(x) o funcție oarecare,
;; Calculați valorile funcției f(x), a < x < b cu pasul step.
;; Atenție: Folosiți named let.
;;          Nu apelați recursiv `compute-f-with-step`.
;;          Nu aveți voie să folosiți funcționale.
(define (compute-f-with-step f a b step)
  'your-code-here)

(check-exp-part 'a (/ 1. 2)  (compute-f-with-step (lambda (x) (* x x)) 0 4 1) '(0 1 4 9 16))
(check-exp-part 'b (/ 1. 2)  (compute-f-with-step (lambda (x) (+ (* 2 x) 1)) 0 4 1) '(1 3 5 7 9))

(exercițiul 5 : 1 puncte)
;; Funcția num-concat primește două numere și le concatenează.
;; ex:
;;   > (num-concat 33 22)
;;   3322
;; Suprascrieți procedura `+` doar în contextul local pentru
;; a realiza concatenarea dintre două numere.
;; Hint: `string-append` concatenează două string-uri
;; Hint: Puteți folosi funcțiile `number->string` și `string->number`
(define (num-concat x y)
  'your-code-here
    (+ x y));; Nu stergeți această linie.

(check-exp-part 'a (/ 1. 2) (num-concat 1 2) 12)
(check-exp-part 'b (/ 1. 2) (num-concat 33 674) 33674)

(exercițiul 6 : 3 puncte)
;; Definiți funcția compute-perimeter care primește un poligon reprezentat
;; printr-o listă de puncte și calculează perimetrul acestuia.
;; Atenție: Nu aveți voie să definiți funcții ajutătoare în exteriorul funcției compute-perimeter.
;;          Nu aveți voie să folosiți funcționale.
;; Hint: Folosiți-vă de funcția distance
(define (compute-perimeter points)
  'your-code-here)

(check-exp-part 'a (/ 1. 4) (compute-perimeter (list '(1 . 0) '(0 . 0) '(0 . 1) '(1 . 1))) 4)
(check-exp-part 'b (/ 1. 4) (compute-perimeter (list '(2 . 0) '(0 . 0) '(0 . 2) '(2 . 2))) 8)
(check-exp-part 'c (/ 1. 4) (compute-perimeter (list '(2 . 5) '(5 . 43) '(43 . 43))) 132.01993654258658)
(check-exp-part 'd (/ 1. 4) (compute-perimeter (list '(2 . 2) '(4 . 5) '(0 . 3) '(4 . 3) '(3 . 1))) 15.727968770336455)

(exercițiul 7 : 2 puncte)
;; Se dau 3 secvențe separate printr-un separator.
;; Definiți funcția `3-sequence-max` care găsește
;; suma secvenței de sumă maximă.
;; ex:
;; (1 2 3 0 3 5 4 0 5 200) => secvența de sumă maximă este 205
;; Atenție: Nu aveți voie să folosiți fold/apply.
;;          Folosiți let-values/let*-values.
;; Hint:: Uitați-vă peste splitf-at.
(define (3-sequence-max numbers separator)
  'your-code-here)

(check-exp-part 'a (/ 1. 2) (3-sequence-max '(1 0 2 0 3) 0) 3)
(check-exp-part 'b (/ 1. 2) (3-sequence-max '(2 3 4 0 4 105 6 0 54 5) 0) 115)

(exercițiul 8 : 2 puncte BONUS)
;; Redefiniți funcția num-concat pentru a funcționa pe oricâte numere.
;; Atenție: Nu puteți folosi `num-concat`
;;          Folosiți funcționale.
;; Înțelegeți cum vă poate ajuta programarea funcțională?
;; Cum ar arăta o suprascriere echivalentă într-un limbaj procedural?
;; Care implementare este mai straightforward, este mai ușor de înțeles
;; și lasă loc pentru mai puține erori?
(define (list-num-concat numbers)
  'your-code-here)

;; Definiți funcția care gasește toate sufixele posibile pentru un număr.
;; ex:
;; (find-all-suffixes 123) => '(123 23 3)
;; Atenție: Folosiți named let.
;;          Există deja definită in laborator funcția number->list.
(define (find-all-suffixes number)
  'your-code-here)

(check-exp-part 'a (/ 1. 2) (find-all-suffixes 1234) '(1234 234 34 4))
(check-exp-part 'b (/ 1. 2) (find-all-suffixes 56789462782) '(56789462782 6789462782 789462782 89462782 9462782 462782 62782 2782 782 82 2))

(exercițiul 9 : 1 puncte BONUS)
;; Automatele finite sunt un formalism matematic util pentru a descrie
;; în mod abstract (matematic) procese, sunt folosite des în computer science
;; și le veți întâlni (le-ați întâlnit) la CN, LFA și alte materii.
;; În acest exercițiu vom reprezenta un automat finit prin 3 elemente:
;;    initial-state => o stare inițială din care automatul pornește
;;    final-state => o stare finală în care automatul se oprește
;;    next => o funcție care primește o stare și decide care e următoarea stare.
;; Determinați ordinea de parcurgere a stărilor în urma executării automatului.
;; O execuție a automatului începe din starea inițială initial-state, parcurge
;; stările conform funcției de tranziție next și se încheie în starea finală,
;; ordinea de parcurgere fiind reprezentată sub forma unei liste de stări.
;; Atenție: Trebuie să folosiți named let.
(define (run initial-state final-state next)
  'your-code-here)

(check-exp-part 'a (/ 1. 4) (run 0 9 add1) (range 10))
(check-exp-part 'b (/ 1. 4) (run 9 0 sub1) (reverse (range 10)))
(check-exp-part 'b (/ 1. 4) (run 0 20 (compose add1 add1)) (filter even? (range 21)))
(check-exp-part 'b (/ 1. 4) (run 2 65536 (lambda (x) (* x x))) '(2 4 16 256 65536))

(exercițiul 10 : 2 puncte BONUS)
;; Folosindu-vă de exerciţiile anterioare generați numărul de lungime k
;; pentru care orice cifră de pe poziția i se poate obține
;; folosind formula i*k+x.
;; Atenție: Folosiți funcția run.
(define (generate-number k x)
  'your-code-here)

(check-exp-part 'c (/ 1. 2) (generate-number 3 2) 258)
(check-exp-part 'd (/ 1. 2) (generate-number 3 3) 369)

(sumar)
