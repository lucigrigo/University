#lang racket

(define (stream-gen n1 n2 n3)
  (stream-cons
   (* n1 (expt n2 n3))
   (stream-gen n1 n2 (add1 n3))))

(foldl + 0 (stream-take (stream-gen 1 2 0) 10000))
