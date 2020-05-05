#lang racket

(provide fill-abilities)
(provide compose-abilities)
(provide hourglass)
(provide position-abilities)
(provide get-ability-image)
(provide get-ability-time)
(provide get-ability-pos)
(provide get-ability-next)
(provide check-ability-active)
(provide ability-state)
(provide ability-state-time)
(provide ability-state-pos)
(provide ability-state-image)
(provide ability-state-active)

(require "random.rkt")
(require lang/posn)
(require 2htdp/image)

; Imaginea si range-ul în care vor aparea abilitațile
; Nu modificați
(define POSITION_RANGE '((300 2000) (30 550)))
(define (hourglass color) (underlay
 (rectangle 40 40 "solid" color)
 (polygon
  (list (make-posn 0 0)
        (make-posn 25 0)
        (make-posn 0 25)
        (make-posn 25 25))
  "outline"
  (make-pen "darkslategray" 5 "solid" "round" "round"))))


; Fiecare funcție returneaza o componenta a unei abilități.
(struct ability-state
  (image time pos next active) #:transparent)

(define (get-ability-image ability)
  (ability-state-image ability))

(define (get-ability-time  ability)
  (ability-state-time ability))

(define (get-ability-pos ability)
  (ability-state-pos ability))
  
(define (get-ability-next  ability)
  (ability-state-next ability))

(define (check-ability-active ability)
  (ability-state-active ability))

; Returneaza o poziție aleatorie în POSITION_RANGE.
(define (random-position range)
	(apply make-posn (map ((curry apply) random) range)))

; Returnează o listă de n elemente alese aleatoriu din lista L.
(define (choice-abilities n L)
	(sample (discrete-dist L) n))

; Va parcurge abitatile și pentru cele care au poziția null va asigna
; una aletorie.
; Folosiți random-position
(define (position-abilities abilities)
  (map (λ (ability)
         (if (null? (get-ability-pos ability))
             (struct-copy ability-state ability
                          [pos (random-position POSITION_RANGE)])
              ability))
       abilities))

; Fiecare abilitate are o funcție next care modifica stare jocului
; Compuneti toate funcțiile next în una singură
; Hint: compose
(define (compose-abilities L)
  (foldl (λ (ability f)
           (compose (get-ability-next ability) f))
         identity
         L))

; Primiște o listă de abilități inițiale, un număr n
; și o listă cu toate abilități posibile.
; Va adauga elemente aleatoare la lista inițială pană aceasta are lungimea n
; Atentie n poate fi chiar si 0 cand vrem sa jucam fara nicio abilitate.
; Folosiți choice-abilities.
(define (fill-abilities initial n abilities)
  (if (< (length abilities) n)
      (append abilities
              (position-abilities (choice-abilities (- n (length abilities)) abilities)))
      abilities))
