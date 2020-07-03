#lang racket

(define (f L)
  (if (null? L)
      null
      (cons (car L) (f (cdr L)))))

(f (list 1 2 3 4))

(define (test x)
  (+ x
     (let ((x 1) (y 2))
       (+ x y))))

(test 5)

(define (ff a b)
  (if (= (quotient a b) 5)
      +
      -))

((ff 27 5) 2 1)

(define (magic l n)
  (let ([h (car l)] [t (cdr l)])
    (if (empty? t)
        (cons h n)
        (if (= h (car t))
            (magic t (cons h n))
            (magic t n)))))

(magic `(1 1 4 7 7 7 10) `())

(define (stream-gen n1 n2 n3)
  (stream-cons
   (* n1 (expt n2 n3))
   (stream-gen n1 n2 (add1 n3))))


(let [(do (and (display "a ")
                 (delay (and (display "done ") 2))))
        (whatto (lambda (what) (and (display "w ")
                                    (force what))))]
    (and (display "d ")
         (whatto do)))

(foldl append `(0) (list (list 1 2) (list 3 4) (list 5 6)))

(cons 0 (foldr append '() (reverse (list (list 1 2) (list 3 4) (list 5 6)))))

(apply append (map reverse (cons '(0) (list (list 1 2) (list 3 4) (list 5 6)))))

(reverse (apply append '(0) (list (list 1 2) (list 3 4) (list 5 6))))

(append (apply append (reverse (list (list 1 2) (list 3 4) (list 5 6)))) '(0))

(define (fff g)
  (apply filter g (list (list 23 49 56))))

(fff (lambda(x) (< x 50)))