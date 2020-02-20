#lang racket

; ignorați următoarele linii de cod.
(define show-defaults 2) ; câte exerciții la care s-au întors rezultate default să fie arătate detaliat
(define prepend #f) (define name-ex '(testul testele trecut)) ; variante: '(exercițiul exercițiile rezolvat) sau '(testul testele trecut) sau '(task taskurile rezolvat)
(define default-results `(#f 0 () your-code-here)) ; ce rezultate default sunt întoarse în exerciții
(define : 'separator) (define punct 'string) (define puncte 'string) (define BONUS 'string) (define total 0) (define all '()) (define n-ex 0) (define p-ex 0) (define defaults '())
(define (ex n sep p . s) (set! n-ex n) (set! p-ex p) (set! all (cons (list n p) all))) (define exercițiul ex) (define (p L) (map (λ (e) (display e) (display " ")) L) (newline))
(define (check-exp given expected) (check-exp-part "" 1 given expected)) (define (check-exp-part part per given expected) (check-test part per equal? given expected "diferă de cel așteptat"))
(define (check-in  given expected) (check-in-part  "" 1 given expected)) (define (check-in-part part per given expected) (check-test part per member given expected "nu se află printre variantele așteptate"))
(define (list>setR start end ch-len? L) (if (zero? end) L ((if (<= start 0) list->seteqv identity) (map (λ (e) (if (list? e) (list>setR (sub1 start) (sub1 end) e) e)) L))))
(define (check-set given expected) (check-set-part  "" 1 given expected)) (define (check-set-part part per given expected) (check-test part per (λ (x y) (apply equal? (map list->seteqv `(,given ,expected)))) given expected "nu este echivalent cu cel așteptat"))
(define (check-set-unique given expected) (check-set-unique-part  "" 1 given expected)) (define (check-set-unique-part part per given expected) (check-test part per (λ (x y) (and (apply = (map length `(,given ,expected))) (apply equal? (map list->seteqv `(,given ,expected))))) given expected "nu este echivalent cu cel așteptat"))
(define (check-test part percent tester given expected err-m) (if (not (tester given expected)) (and (when (member given default-results) (set! defaults (cons (if (< percent 1) (cons n-ex part) n-ex) defaults)))
  (when (or (not (member given default-results)) (<= (length defaults) show-defaults))
    (printf "[~a][--]~a rezultatul ~v ~a: ~v~n" n-ex (if (< percent 1) (format " la ~a ~v" (car name-ex) part) "") given err-m expected)))
 (let ((pts (* p-ex percent))) (printf "~a ~a ~a~a~a: +~v ~a~n" (if prepend (format "+~v:" pts) (format "[~v][OK]" n-ex)) (car name-ex) (if prepend n-ex "") (if (< percent 1) (format "~v " part) "") (caddr name-ex) pts (if (= pts 1) 'punct 'puncte)) (set! total (+ total pts)))))
(define (sumar) (when (and (not (null? defaults)) (< show-defaults (length defaults))) (p `(... rezultatul implicit dat la ,(cadr name-ex) ,(reverse defaults)))) (printf "total: ~v puncte~n" total))


;; Avem de implementat o mini-bibliotecă pentru numere palindromice.

;; Pentru aceasta, vom defini, pe rând, funcții pentru:
;; - reprezentarea (ca listă de "cifre") a unui număr natural într-o bază b
;; - testul că o listă este palindrom (adică este totuna cu lista inversată)
;; - testul că un număr este palindrom în toate bazele dintr-o listă dată
;; - parcurgerea tuturor numerelor până la un număr dat n, și selectarea celor
;;   care sunt palindroame în toate bazele dintr-o listă dată de baze
;; - determinarea gradului unui palindrom
;; - determinarea cifrei care poate fi eliminată astfel încât un număr să
;;   devină palindrom

(exercițiul 1 : 2 puncte)
;; Fie următoarele axiome pentru obținerea reprezentării unui număr natural
;; în baza b (cu [] = lista vidă și ++ = concatenare).
;; num->base(0,b) = [ ]                                   ; pt n=0
;; num->base(n,b) = num->base(n div b, b) ++ [ n mod b ]  ; pt n>0
;; Implementați funcția corespunzătoare în Racket:

(define (num->base n b)
  'your-code-here)

(check-exp-part 'a .5 (num->base 489 10) '(4 8 9))
(check-exp-part 'b .5 (num->base 489 2) '(1 1 1 1 0 1 0 0 1))


(exercițiul 2 : 2 puncte)
;; Fie următoarele axiome pentru inversarea unei liste.
;; rev([ ]) = [ ]
;; rev(x:l) = rev(l) ++ [x]
;; Implementați funcția corespunzătoare în Racket:

(define (rev L)
  'your-code-here)

(check-exp (rev '(5 1 4 8 7)) '(7 8 4 1 5))


(exercițiul 3 : 1 punct)
;; Implementați testul că o listă L este palindrom:

(define (palindrome? L)
  'your-code-here)

(check-exp-part 'a .25 (palindrome? '(1 4 4 1)) #t)
(check-exp-part 'b .25 (palindrome? '(1 4 2 4 1)) #t)
(check-exp-part 'c .25 (palindrome? '(1 4 4 1 4 1)) #f)
(check-exp-part 'd .25 (palindrome? '()) #t)


(exercițiul 4 : 2.5 puncte)
;; Testați că n este palindrom în toate bazele din lista Bases:

(define (all-palindromes? n Bases)
  'your-code-here)

(check-exp-part 'a .5 (all-palindromes? 585 '(2 10)) #t)
(check-exp-part 'b .5 (all-palindromes? 594 '(2 10)) #f)


(exercițiul 5 : 2.5 puncte)
;; Găsiți toate numerele naturale, mai mici sau egale cu n, care sunt
;; palindroame în toate bazele din lista Bases:

(define (palindromes-to-n n Bases)
  'your-code-here)

(check-exp (palindromes-to-n 100 '(2 10)) '(0 1 3 5 7 9 33 99))


(exercițiul 6 : 2 puncte BONUS)
;; Să se găsească primul număr mai mare decât start care este palindrom în
;; minim b baze dintre bazele 2, 3, 4, 5, 6, 7, 8, 9, 10.

(define (first-b-pal start b)
  'your-code-here)

(check-exp-part 'a .5 (first-b-pal 10 4) 121)
(check-exp-part 'b .5 (first-b-pal 150 4) 373)


(exercițiul 7 : 3 puncte BONUS)
; Să se găsească cea mai lungă porțiune continuă care este palindrom, dintr-un număr, în baza 10.
(define (list->num L) (foldl (lambda (dig num) (+ dig (* 10 num))) 0 L))
; Hint: funcția (take L n) întoarce prefixul de lungime n al listei L.

(define (longest-palindrome n)
   'your-code-here)

(check-exp-part 'a 1/6 (longest-palindrome 121) 121)
(check-in-part  'b 1/6 (longest-palindrome 51) '(1 5))
(check-exp-part 'c 1/6 (longest-palindrome 1214) 121)
(check-exp-part 'd 1/6 (longest-palindrome 5121) 121)
(check-exp-part 'e 1/6 (longest-palindrome 5122145215) 1221)
(check-exp-part 'f 1/6 (longest-palindrome 5122145213125) 5213125)


(sumar)