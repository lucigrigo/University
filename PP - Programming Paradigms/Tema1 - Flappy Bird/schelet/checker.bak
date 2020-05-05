#lang racket

(require lang/posn)
(require 2htdp/universe)
(require 2htdp/image)


(require "abilities.rkt")
(require "random.rkt")
(require "constants.rkt")
(require "main.rkt")

(define show-defaults 200) ; câte exerciții la care s-au întors rezultate default să fie arătate detaliat
(define prepend #t) (define name-ex '(testul . testele)) ; variante: '(exercițiul . exercițiile) sau '(testul . testele) sau '(task . taskurile)
(define default-results '(#f 0 () your-code-here)) ; ce rezultate default sunt întoarse în exerciții
(define (default-result r) (set! default-results (cons r default-results)))
(define : 'separator) (define punct 'string) (define puncte 'string) (define BONUS 'string) (define total 0) (define all '()) (define n-ex 0) (define p-ex 0) (define defaults '())
(define (ex n sep p . s) (set! n-ex n) (set! p-ex p) (set! all (cons (list n p) all))) (define testul ex) (define (p L) (map (λ (e) (display e) (display " ")) L) (newline))
(define (expart per part) (if (< per 1) (string-append (number->string n-ex) (symbol->string part)) n-ex))
(define (whengood expart per) (let ((pts (* p-ex per))) (and (if prepend (printf "+~v: " pts) (printf "OK: ")) (p `(,(car name-ex) ,expart rezolvat: + ,pts ,(if (= pts 1) 'punct 'puncte))) (set! total (+ total pts)))))
(define (whenbad expart gvn expcd) (and (when (member gvn default-results) (set! defaults (cons expart defaults))) (when (or (not (member gvn default-results)) (<= (length defaults) show-defaults)) (bad-res expart gvn expcd))))
(define (bad-res expart gvn expcd . c) (p (append `(NU: la ,(car name-ex) ,expart rezultatul ,gvn) (if (null? c) `(diferă de cel așteptat: ,expcd) c))))
(define (check-cond part per gvn tests) (let ((r ((car tests) gvn))) (if (eq? r #t) (apply check-exp-cond part per gvn (cdr tests)) (bad-res (expart per part) gvn #f (or r "nu îndeplinește condiția")))))
(define (check-exp given expected) (check-exp-part "" 1 given expected))
(define (check-exp-part part per gvn expcd) (let ((expart (expart per part))) (if (equal? gvn expcd) (whengood expart per) (whenbad expart gvn expcd))))
(define (check-exp-cond part per gvn . tests) (if (member gvn default-results) (whenbad (expart per part) gvn (last tests)) (if (null? (cddr tests)) (check-exp-part part per ((car tests) gvn) (cadr tests)) (check-cond part per gvn tests))))
(define (sumar) (when (and (not (null? defaults)) (< show-defaults (length defaults))) (p `(... rezultatul implicit dat la ,(cdr name-ex) ,(reverse defaults)))) (p `(total: ,total puncte)))
(define (mark-helper) (printf "---~nEx  puncte    Total până aici~n") (foldr (λ (e-p t) (p `(,(car e-p) : ,(cadr e-p) puncte. total 1 - ,(car e-p) : ,(+ t (cadr e-p)))) (+ t (cadr e-p))) 0 all))

(define (repeater f acc count) (if (equal? count 0)
			       acc
			       (repeater f (f acc) (- count 1))))
;echivalent (f(f(f...(f acc)..))), de count ori, folosit pentru apeluri succesive de next-state*

(define next-state-i (lambda (initial-state i) (repeater (lambda (state) (next-state state)) initial-state i)))

(disable-score)
(disable-bonus)
(make-predictive '(42))

(define initial-state (get-initial-state))
(define initial-bird (get-bird initial-state))
(define initial-pipes (get-pipes initial-state))
(define initial-score (get-score initial-state))

(testul 0 : 10 puncte) ;bird
;Adaugarea in state a pasarii; pasarea se afla initial pe y-ul specificat
(check-exp-part `-bird-in-state (/ 4. 10) (get-bird-y initial-bird) bird-initial-y)
;next-state-bird imprima vitezei pasarii gravitatia
(check-exp-part `-gravity-test (/ 4. 10) (get-bird-v-y (next-state-bird initial-bird initial-gravity)) initial-gravity)
;next-state imprima vitezei pasarii gravitatia
(check-exp-part `-gravity-integration-into-next-state (/ 2. 10) (get-bird-v-y (get-bird (next-state initial-state))) initial-gravity)


(testul 1 : 5 puncte) ;change
;next-state-bird-onspace imprima pasarii un impuls
(check-exp-part `-momentum-test (/ 5. 10) (get-bird-v-y (next-state-bird-onspace initial-bird initial-momentum)) (- initial-momentum))
;change apelat cu tasta "space" imprima pasarii un impuls
(check-exp-part `-momentum-integration-into-change (/ 5. 10) (get-bird-v-y (get-bird (change initial-state " "))) (- initial-momentum))


(testul 2 : 20 puncte) ;pipes
;Adaugarea in state a primului pipe; acesta va avea x-ul specificat
(check-exp-part `-first-pipe-in-state (/ 1. 10) (get-pipe-x (car initial-pipes)) scene-width)
;move-pipes misca pipe-urile
(check-exp-part `-move-pipes-test (/ 2. 10) (get-pipe-x (car (move-pipes initial-pipes initial-scroll-speed))) (- scene-width initial-scroll-speed))
;clean-pipes sterge pipe-urile care au iesit de pe ecran
(check-exp-part `-clean-pipes-test (/ 2. 10) (length (clean-pipes (repeater (lambda (pipes) (move-pipes pipes initial-scroll-speed)) initial-pipes 10000))) 0)
;add-more-pipes adauga cate un pipe, daca sunt mai putin de no-pipes
(check-exp-part `-add-more-pipes-test (/ 2. 10) (length (repeater add-more-pipes initial-pipes no-pipes)) no-pipes)
;integrare cu next-state-pipes
(check-exp-part `-next-state-pipes-integration (/ 2. 10) (length (next-state-pipes initial-pipes initial-scroll-speed)) 2)
;integrare cu next-state
(check-exp-part `-next-state-integration (/ 1. 10) (length (get-pipes (next-state initial-state))) 2)


(testul 3 : 5 puncte) ;scorul
;Adaugarea in state a scorului
(check-exp-part `-score-in-state (/ 5. 10) (get-score initial-state) 0)
;next-state mareste scorul
(check-exp-part `-next-state-increases-score (/ 5. 10) (get-score (next-state initial-state)) 0.1)


(testul 4 : 30 puncte) ;draw-frame functioneaza corect
(check-exp-part `-check-draw-frame (/ 1. 10)  (draw-frame initial-state) (bitmap/file "ref/5/0/0.png"))
(check-exp-part `-check-draw-frame-with-pipes (/ 1. 10)  (draw-frame (next-state initial-state)) (bitmap/file "ref/5/1/0.png"))
(define frames-to-check '(1 8 19))
(check-exp-part `-check-draw-frames (/ 4. 10)
		(map (compose draw-frame ((curry next-state-i) initial-state)) frames-to-check)
		(map (lambda (i) (bitmap/file (~a "ref/5/2/" i ".png"))) frames-to-check))
(check-exp-part `-check-draw-frames-with-space (/ 4. 10)
		(map (compose draw-frame ((curry next-state-i) (change initial-state " "))) frames-to-check)
		(map (lambda (i) (bitmap/file (~a "ref/5/3/" i ".png"))) frames-to-check))


(testul 5 : 30 puncte) ;valid-state?; coliziuni
;check-ground-collision returneaza false cand nu avem coliziune cu pamantul
(check-exp-part `-check-ground-collision-#f (/ 1. 20) (check-ground-collision initial-bird) #f)
;---si true, in caz contrar
(check-exp-part `-check-ground-collision-#t (/ 1. 20) (check-ground-collision (repeater (lambda(bird) (next-state-bird bird initial-gravity)) initial-bird 100)) #t)

;integrare check-ground-collision in invalid-state?
(check-exp-part `-check-ground-collision-integration-into-invalid-state? (/ 2. 20) (invalid-state? (repeater next-state initial-state 100)) #t)

;check-pipe-collisions returneaza false cand nu avem coliziune cu pipes
(check-exp-part `-check-pipe-collisions-#f (/ 1. 20) (check-pipe-collisions initial-bird initial-pipes) #f)
;coliziune pasare pipes inferior
(check-exp-part `-check-pipe-collisions-lower-#t (/ 4. 20) (check-pipe-collisions
							     (repeater (lambda(bird)
									 (next-state-bird (next-state-bird-onspace bird initial-momentum) initial-gravity))
								       initial-bird 0)
							     (repeater (lambda(pipes) (next-state-pipes pipes initial-scroll-speed)) initial-pipes 50))
							     #t)
;coliziune pasare pipes superior
(check-exp-part `-check-pipe-collisions-upper-#t (/ 4. 20) (check-pipe-collisions
							     (repeater (lambda(bird)
									 (next-state-bird (next-state-bird-onspace bird initial-momentum) initial-gravity))
								       initial-bird 22)
							     (repeater (lambda(pipes) (next-state-pipes pipes initial-scroll-speed)) initial-pipes 50))
							     #t)
;nu are coliziune intre pipes
(check-exp-part `-check-pipe-collisions-between-#f (/ 4. 20) (check-pipe-collisions
							     (repeater (lambda(bird)
									 (next-state-bird (next-state-bird-onspace bird initial-momentum) initial-gravity))
								       initial-bird 21)
							     (repeater (lambda(pipes) (next-state-pipes pipes initial-scroll-speed)) initial-pipes 50))
							     #f)
;integrare check-pipe-collisions in invalid-state?
(check-exp-part `-check-pipe-collision-integration-into-invalid-state? (/ 3. 20)
		(invalid-state? (repeater
		  (lambda(state)
		    (repeater
		      (lambda(state)
			(next-state state))
		      (change state " ")
		      10))
		  initial-state
		  5))
		#t)


(enable-bonus)
(make-predictive '(32 100 200 150 300 240 80 432 300))

(testul 6 : 10 puncte BONUS)
(let* ([state (next-state initial-state)]
		  [visible (get-abilities-visible (get-abilities state))])
	(check-exp-part `-check-visible-ability-position (/ 3. 10) (map get-ability-pos visible)
		(list (make-posn 100 200)
					(make-posn 150 300)
					(make-posn 240 80)
					(make-posn 432 300)))
	(check-exp-part `-check-visible-ability-time (/ 1. 10) (map get-ability-time visible) '(30 10 30 30))
	(check-exp-part `-check-visible-ability-image (/ 1. 10) (map get-ability-image visible)
		(list (hourglass "tomato")
					(hourglass "mediumseagreen")
					(hourglass "tomato")
					(hourglass "tomato")))
	(check-exp-part `-check-visible-ability-draw-frame (/ 5. 10) (draw-frame state) (bitmap/file "ref/7/0.png")))

(define frames-to-check-bonus '(1 8))


(make-predictive (list 32 (+ bird-x 100) (- bird-initial-y 90) (+ bird-x 120) (- bird-initial-y 110) 5000))

(testul 7 : 10 puncte BONUS)
(let* ([state (change (next-state initial-state) " ")]
			[next-state (next-state-i state 8)]
			[active (get-abilities-active (get-abilities next-state))])
	(check-exp-part `-check-active-ability-time (/ 1. 4) (and (equal? (length active) 2) (andmap < (map get-ability-time active) '(30 10))) #t)
	(check-exp-part `-check-active-ability-image (/ 1. 4) (map get-ability-image active)
		(list (hourglass "tomato")
					(hourglass "mediumseagreen")))
	(check-exp-part `-check-active-ability-draw-frames (/ 2. 4)
			(map (compose draw-frame ((curry next-state-i) state)) frames-to-check-bonus)
			(map (lambda (i) (bitmap/file (~a "ref/8/" i ".png"))) frames-to-check-bonus)))

(sumar)
