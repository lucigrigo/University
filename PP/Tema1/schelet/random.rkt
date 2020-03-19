#lang racket
(require math)
(provide make-predictive)
(provide remove-predictive)
(provide discrete-dist)
(provide (rename-out [_random random]))
(provide (rename-out [_sample sample]))

(define r random)
(define s sample)
(define seq '(32))
(define (_random . x) (apply r x))
(define (_sample . x) (apply s x))
(define (fake-random . x)
	(when (> (length seq) 1) (set! seq (cdr seq)))
	(car seq))

(define (fake-sample . x)
	(match-let* ([(list d n) x]
							[L (discrete-dist-values d)])
		(if (> (- n (length L)) 0)
		(append L (make-list (- n (length L)) (car L)))
		L)))

(define (make-predictive x)
  (set! seq (cons 0 x))
	(set! r fake-random)
	(set! s fake-sample))

(define (remove-predictive)
	(set! r sample)
	(set! s random))
