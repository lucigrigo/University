#lang racket
(require lang/posn)
(provide (all-defined-out))

(define fps 28.0)

(define scene-height 960)
(define scene-width 640)

(define ground-height (quotient scene-height 6))
(define ground-y (- scene-height ground-height))

(define initial-gravity 1.3)
(define initial-momentum 15.0)

(define bird-width 81)
(define bird-height 57)
(define bird-x (quotient scene-width 3))
(define bird-initial-y (quotient scene-height 2))

(define pipe-width 104)
(define pipe-height scene-height)
(define pipe-gap 232.75)
(define pipe-self-gap 280)

(define initial-scroll-speed 7.0)

(define added-number (quotient scene-height 8))
(define random-threshold (- (- scene-height (* 2 added-number)) pipe-self-gap))

(define no-pipes 6)
(define text-x (- scene-width 50))
(define text-y 50)
(define abilities-posn (make-posn (- scene-width 50) 80))
(define DISPLAYED_ABILITIES 4)

; checker stuff
(define (disable-bonus) (set! DISPLAYED_ABILITIES 0))
(define (enable-bonus) (set! DISPLAYED_ABILITIES 4))
