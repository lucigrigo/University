#lang racket

;; Exercitiul 1 - decomentati apelurile de mai jos pentru a 
;; observa comportamentul functiilor curry/uncurry
;; exercitiul a fost prezentat si la curs
(define add-curry
  (lambda (x)
    (lambda (y)
      (+ x y))))

;((add-curry 2) 5)       ;; 7 - observati apelul: intai (add-curry 2), apoi rezultatul aplicat pe 5
;(add-curry 2)           ;; #<procedure> - va fi o noua functie care asteapta un argument 
                        ;; pentru a il aduna cu 2

(define add-uncurry
  (lambda (x y)
    (+ x y)))

;(add-uncurry 2 5)       ;; 7
;(add-uncurry 2)         ;; procedure add-uncurry: expects 2 arguments, given 1: 2
                        ;; deci o eroare, intrucat o functie uncurry trebuie sa isi primeasca
                        ;; toate argumentele deodata

(define inc-curry (add-curry 1))
;(inc-curry 5)           ;; 6 - inc-curry este exact functia increment, definita aici cu
                        ;; minim de efort pe baza functiei add-curry
                        ;; ceea ce produce (add-curry 1) este (lambda (y) (+ x y)) cu x legat la 1

(define (inc-uncurry x) 
  (add-uncurry 1 x))
;(inc-uncurry 5)         ;; 6 - aceeasi functie increment, insa definita mai greoi (e nevoie de parametru)

;; Exercitiul 2 - mai multa reutilizare de cod, de data asta 
;; pentru a particulariza o functie de sortare
;; dupa orice tip de comparator
(define (ins-in-sorted op)
  (lambda (e L)
    (if (or (null? L) (op e (car L)))     ;; op = un operator de comparatie
        (cons e L)
        (cons (car L) ((ins-in-sorted op) e (cdr L))))))

(define (sort-ins op)
  (lambda (L)
    (if (null? L)
        L
        ((ins-in-sorted op) (car L) ((sort-ins op) (cdr L))))))

(define sort-ascending (sort-ins <=))
(define sort-descending (sort-ins >=))
(define sort-mod5 (sort-ins (lambda (x y) (< (modulo x 5) (modulo y 5)))))

;(sort-ascending '(6 1 7 9 3 2 4 6 7))      ;; o functie de sortare crescatoare
;(sort-descending '(6 1 7 9 3 2 4 6 7))     ;; o functie de sortare descrescatoare
;(sort-mod5 '(6 1 7 9 3 2 4 6 7))           ;; o functie de sortare dupa restul la impartirea cu 5

;; Observatie: sortarea mod 5 ar putea folosi o functie derivata dintr-o comparatie mod x, cu x oarecare
;; puteti incerca asta ca exercitiu

;; Exercitiul 3 - implementarea functionalei map
(define (map1 f L)
  (if (null? L)
      L
      (cons (f (car L)) (map1 f (cdr L)))))

;(map1 (lambda (x) (* 2 x)) '(1 2 3 4 5))
;(map1 (lambda (x) (even? x)) '(1 2 3 4 5))
;(map1 (lambda (x) (remainder x 3)) '(4 5 7 8 9 1))

;; Exercitiul 4 - implementarea functionalei filter
(define (filter1 p L)
  (cond
    ((null? L) L)
    ((p (car L)) (cons (car L) (filter1 p (cdr L))))
    (else (filter1 p (cdr L)))))

;(filter1 even? '(1 2 3 4 5 6 7 8))
;(filter1 positive? '(-3 -4 5 6 -8 2 -1))

;; Exercițiul 5 - implementarea funcționalei foldl
(define (foldl1 p acc L)
  (if (null? L)
      acc
      (foldl1 p (p (car L) acc) (cdr L))))

;(foldl1 + 0 '(1 2 3 4))
;(foldl1 (lambda (x acc) (if (>= x 10) (cons x acc) acc)) null '(1 3 10 11 4 12))
;(foldl1 cons null '(1 2 3 4))

;; Exercițiul 6 - implementarea funcționalei foldr
(define (foldr1 p acc L)
  (if (null? L)
      acc
      (p (car L) (foldr1 p acc (cdr L)))))

;(foldr1 + 0 '(1 2 3 4))
;(foldr1 cons null '(1 2 3 4))
;(foldr1 (lambda (x acc) (if (>= x 10) (cons x acc) acc)) null '(1 3 10 11 4 12))

;; Exercitiul 7 - suma elementelor unei liste utilizand apply
(define (sumlist L)
  (apply + L))

; (sumlist '(1 2 3 4 5))

;; Exercitiul 8 - suma elementelor unei liste utilizand foldr
(define (sumlist2 L)
  (foldr + 0 L))

; (sumlist2 '(1 2 3 4 5))

;; Exercitiul 9 - inversarea unei liste utilizand foldl
(define (reverselist L)
  (foldl cons null L))

; (reverselist '(1 2 3 4 5 6))

;; Exercițiul 10 BONUS - implementarea funcționalei apply
;; Pentru mai multe detalii legate de namespace și eval, accesati documentatia de Racket
;; (eval: Racket Documentation -> The Racket Guide -> Reflection and Dynamic Evaluation -> eval)
;; (namespaces: Racket Documentation -> The Racket Reference -> Language Model -> Syntax Model -> Namespaces)
(define (apply1 fun args)
  (eval (map (lambda (x) (list 'quote x)) (cons fun args)) (make-base-namespace)))

;(apply1 + '(1 2 3))
;(apply1 cons '(1 2))