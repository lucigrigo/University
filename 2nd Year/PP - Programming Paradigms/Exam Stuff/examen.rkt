#lang racket
(define (t x)
  (cond ((or (< x 0) (even? x)) 0)
             ((< x 5) (quotient x 2))
             (else (+ (t (- x 2)) (t (- x 4))))))
(t 11)

(define (tt x acc)
  (cond ((or (< x 0) (even? x)) 0)
        ((< x 5) acc)
        (else (tt (- x 4) (+ acc x)))))

(tt 11 1)

(define (intersect L1 L2)
  (foldr (λ (e acc)
           (if (equal? (length (filter (λ (x) (equal? e x)) L2)) 0)
               acc
               (cons e acc))) `() L1))

(define (construct F1 F2)
  (stream-cons (intersect (stream-first F1) (stream-first F2))
               (construct (stream-rest F1) (stream-rest F2))))