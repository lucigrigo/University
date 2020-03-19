#lang racket

(require 2htdp/image)
(require 2htdp/universe)

; ----- Structuri -----

; Definirea unei structuri ball, cu trei câmpuri, x, y și color.
; Transparent permite afișarea valorilor câmpurilor.
(define-struct ball (x y color) #:transparent)

; Definirea unui obiect structură.
(define b1 (ball 2 3 "red"))
b1

; Accesul la câmpuri se face prin funcțiile <structură>-<câmp>.
(ball-x b1)
(ball-y b1)
(ball-color b1)

; „Modificarea” câmpurilor x și y. Câmpurile nemenționate explicit
; își mențin valoarea.
; Atragem din nou atenția că nu există nicio modifcare propriu-zisă
; a obiectului existent, ci se creează un nou obiect, cu noile valori
; ale câmpurilor.
(struct-copy ball b1 [x 17] [y 42])

; Există o formă specială de let, cu pattern matching, care permite
; radiografierea unei structuri, cu evidențierea câmpurilor din interior.
(match-let ([(ball x y color) b1])
  (+ x y))

; Există și o formă specială de lambda, care permite radiografierea
; parametrului funcției. Underscore permite ignorarea anumitor câmpuri.
(map (match-lambda [(ball x y _) (+ x y)]) (list b1 b1))
; Echivalent cu
(map (lambda (b) (+ (ball-x b) (ball-y b))) (list b1 b1))

; ----- Universe -----

(define WIDTH 300)
(define HEIGHT 300)
(define OFFSET 10)

; Starea inițială a lumii, reprezentată printr-un obiect ball, situat la coordonatele
; (20, 20) și având culoarea roșie.
(define initial-state (ball 20 20 "red"))

; Funcția care primește ca parametru starea și întoarce reprezentarea ei vizuală
; sub forma unei imagini. Aceasta conține o scenă goală cu lățime și înălțime fixată,
; deasupra căreia se află mingea.
(define (draw-frame state)
  (match-let ([(ball x y color) state])
    (place-image (circle 10 "solid" color) x y (empty-scene WIDTH HEIGHT))))

; Funcția apelată la fiecare bătaie de ceas (tick), care determină starea următoare
; pe baza celei curente. În cazul de față, mingea se deplasează lent și constant pe diagonală.
(define (next-state state)
  (match-let ([(ball x y _) state])
    (struct-copy ball state [x (+ x 1)] [y (+ y 1)])))

; Funcția care ia ca parametru starea curentă și tasta apăsată și construiește
; noua stare. În cazul de față, mingea poate fi controlată cu cele patru săgeți.
(define (change state pressed-key)
  (match-let ([(ball x y _) state])
    (cond [(key=? pressed-key "left")  (struct-copy ball state [x (- x OFFSET)])]
          [(key=? pressed-key "right") (struct-copy ball state [x (+ x OFFSET)])]
          [(key=? pressed-key "up")    (struct-copy ball state [y (- y OFFSET)])]
          [(key=? pressed-key "down")  (struct-copy ball state [y (+ y OFFSET)])]
          [else state])))

; Funcția finală, care integrează funcțiile definite mai sus și pornește animația
(big-bang initial-state
  [on-tick next-state (/ 1.0 30)]  ; fps
  [to-draw draw-frame]
  [on-key change])
