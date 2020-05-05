#lang racket

;; DrRacket pune la dispoziție o funcție de tracing.
(require (lib "trace.ss"))

;; Exercițiul 1 - folosirea funcției trace pentru a înțelege mai bine desfășurarea recursivității

(define (factorial n)
  (if (= n 1)
      1
      (* n (factorial (- n 1)))))

;; Acum putem observa direct cum arată execuția funcției factorial:
;(trace factorial)
;(factorial 10)

;; Ce trebuie reținut în memoria programului la un moment dat:
;; - argumentul n curent (de ex 1)
;; - un număr x de operații care trebuie efectuate pe revenire (de ex înmulțirea cu 2, înmulțirea cu 3 etc)
;;
;; - avansul în recursivitate are loc de O(n) ori, când se și depun informații pe stivă, având un volum O(n)
;; - calculul propriu-zis se desfășoară pe revenirea din recursivitate, când se efectuează O(n) operații
;; - mai durează și înmulțirile ceva, fiind vorba de numere mari
;; - fiecare nivel de recursivitate așteaptă că problema să se întoarcă din nou la el,
;;   că să ajusteze rezultatul așa cum numai el știe!

;; Rulați această funcție factorial pe numere din ce în ce mai mari.
;; Observați durata de rulare.
;(time (factorial 10000))

(define (factorial2 n) ;; acest apel produce redefinirea funcției factorial
  (fact-iter 1 1 n))

(define (fact-iter product counter max-count)
  (if (> counter max-count)
      product
      (fact-iter (* counter product)
                 (+ counter 1)
                 max-count)))

;; Acum putem observă direct cum arată execuția funcției factorial iterativ.
;(trace fact-iter)
;(factorial2 5)

;; Ce trebuie reținut în memoria programului la un moment dat:
;; - argumentul n, argumentul n curent și rezultatul parțial (de ex 1, 6)
;; - nimic altceva
;;
;; - avansul în recursivitate are loc de O(n) ori, când are loc și calculul propriu-zis
;; - nu se efectuează operații pe revenirea din recursivitate
;; - ca și mai sus, o partedin timpul rulării e dedicat înmulțirii de numere mari
;; - un anumit nivel de recursivitate se întâlnește o singură dată cu problema, 
;;   o dă mai departe în formă simplificată și poate uita de ea imediat!
;; - de aceea această formă de recursivitate se numește "pe coadă" - 
;;   pentru că apelul recursiv este ultimul lucru carese întâmplă (este la coadă)

;; Rulați această funcție factorial pe numere din ce în ce mai mari.
;; Observați durata de rulare.
;(time (factorial 10000))

;; Exercițiul 2 - același lucru pentru funcția fibonacci

(define (fib n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fib (- n 1))
                 (fib (- n 2))))))

;(trace fib)
;(fib 5)

;; - în program se reține calea de revenire (pe stivă) și pentru
;;   apelul curent se rețin n și cele 2 rezultate parțiale
;;   de la fib apelat cu (n-1) și (n-2)
;; - numărul de apeluri recursive este 2 din fiecare fib unde n >= 2
;;   iar per total este 2 * (valoarea_returnata) - 1.  Asta se deduce
;;   observând că pe cel mai jos nivel valorile de adunat sunt toate "1",
;;   iar când fib nu întoarce 1 direct, efectuează o adunare.  Pentru
;;   a adună un șir de K elemente două câte două, e nevoie de K-1 operații
;;   de adunare.  Cum toate valorile "șirului" inițial sunt 1, e clar că 
;;   numărul K este egal cu suma finală, și deci vor fi K apeluri din care
;;   avem rezultat direct 1, și K-1 apeluri care vor face sume pe revenire,
;;   deci total 2K-1, cu K = (fib n).
;; - operații pe revenirea din recursivitate:  1 la fiecare fib
;;   neterminal în arbore (adunarea), și (fib n)-1 în total.

(define (fib2 n)
  (fib-iter 1 0 n))

(define (fib-iter a b count)
  (if (= count 0)
      b
      (fib-iter (+ a b) a (- count 1))))

;(trace fib-iter)
;(fib2 5)

;; Varianta iterativă are O(n) timp, și O(1) spațiu
;; Varianta recursivă are O(fib n) timp, și O(n) spațiu
;; Atât la spațiu cât și la timp varianta recursivă este mai ineficientă,
;; mai ales în privința timpului, având în vedere că (fib n) este exponențial în n.

;; Exercițiul 3 - suma elementelor unei liste - varianta iterativă

(define (sum-list L)
  (sum-list-iter 0 L))

(define (sum-list-iter sum L)
  (if (null? L)
      sum
      (sum-list-iter (+ sum (car L)) (cdr L))))

;(trace sum-list-iter)
;(sum-list '(1 2 3 4 5))
  
;; Explicație: pornesc din starea "mai am de adunat elementele din toată lista"
;; și "până acum nu am adunat nimic", și iau câte un element de la
;; începutul părții rămase, și îl adun la ce am adunat până acum.
;; Când nu mai am nimic rămas de prelucrat, înseamnă că am acumulat
;; toată suma în variabila sum și pot să întorc rezultatul final.

;; Exercițiul 4 - lungimea unei liste - varianta iterativă

(define (len L)
  (len-iter 0 L))

(define (len-iter result L)
  (if (null? L)
      result
      (len-iter (+ 1 result) (cdr L))))

;(trace len-iter)
;(len '(1 a 2 b 3 c 4 d 5 e))

;; Exercițiul 5 - append între 2 liste - varianta iterativă

(define (app A B)
  (app-iter B (reverse A)))

(define (app-iter B Result)
  (if (null? B)
      (reverse Result)
      (app-iter (cdr B) (cons (car B) Result))))

;(trace app-iter)
;(app '(1 2 3 4 5) '(a b c))

;; O problemă comună a soluțiilor recursive pe coadă este că
;; rezultatul este construit în ordinea greșită. Se întâmplă din cauză
;; că folosim cons drept constructor de liste, care adaugă doar la
;; început. Soluția uzuală este folosirea funcției reverse
;; pentru inversarea rezultatului înainte de return.