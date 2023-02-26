;;; a) merge two sorted lists(with duplicates)


(defun mergeLists (a b)
	(cond
		((null a) b)
		((null b) a)
		((<= (car a) (car b)) (cons (car a) (mergeLists (cdr a) b)))
		((>= (car a) (car b)) (cons (car b) (mergeLists a (cdr b))))
	)
)

(print "a) Merge [1, 2, 4, 5] with [1, 2, 3]:")
(print (mergeLists '(1 2 4 5) '(1 2 3)))

(defun testMergeLists ()
	(assert
		(and 
			(equal (mergeLists '(1 2 3) '(1 2 4 5)) '(1 1 2 2 3 4 5))
			(equal (mergeLists '() '(1 2 3)) '(1 2 3))
			(equal (mergeLists '(1 2 3) '()) '(1 2 3))
		)
	)
)
(print "Test:")
(print (testMergeLists))

;;; ###############################################################################################################

;;; b) replace an element in L1 by all the elements of L2

(defun concat (l k)
	(if (null l) k
	(cons (car l) (concat (cdr l) k))
	)
)

;(print (concat '(1 2 3) '(4 5 6))) 

(defun replaceElem (l e r) ; list element replacement_list
	(cond
		((null l) ())
		((listp (car l)) (cons (replaceElem (car l) e r) (replaceElem (cdr l) e r)))  ; if element in big list is a list
		((equal e (car l)) (concat r (replaceElem (cdr l) e r)))
		(t (cons (car l) (replaceElem (cdr l) e r)))
	)
)

(terpri)
(print "b) Replace in [1, 2, [1, 4], 1, [3, 2, [1, 5]]] element 1 with [7, 8]:")
(print (replaceElem '(1 2 '(1 4) 1 '(3 2 '(1 5))) '1 '(7 8)))

(defun testReplaceElem ()
	(assert
		(and
			(equal (replaceElem '(1 2 '(1 4)) '1 '(7 8)) '(7 8 2 '(7 8 4)))
			(equal (replaceElem '() 1 '()) '())
			(equal (replaceElem '() 1 '(7 8)) '())
		)
	)
)

(print "Test:")
(print (testReplaceElem))

;;; ###############################################################################################################

;;; c) sum of two numbers as lists (result as list)


(defun digit (l k c)
    (cond
        ((null l) (mod (+ k c) 10))
        ((null k) (mod (+ l c) 10))
        (T (mod (+ l k c) 10))
    )
)

;(print (digit nil 9 1))

(defun carry (l k c)
    (cond
        ((null l) (if (> (- (+ k c) (mod (+ k c) 10)) 9) 
                      (/ (- (+ k c) (mod (+ k c) 10)) 10) 
                      (mod (+ k c) 10)
                  )
        )
        ((null k) (if (> (- (+ l c) (mod (+ l c) 10)) 9)
                      (/ (- (+ l c) (mod (+ l c) 10)) 10) 
                      (mod (+ l c) 10)
                  )
        )
        (T (if (> (- (+ l k c) (mod (+ l k c) 10)) 9)
                      (/ (- (+ l k c) (mod (+ l k c) 10)) 10) 
                      (mod (+ l k c) 10)
                  )
        )
    )
)

;(print (carry 9 nil 1))


(defun myAppend (l k)
    (if (null l) 
        k
        (cons (car l) (myAppend (cdr l) k))
    )
)

(defun myReverse (l)
    (cond
        ((null l) nil)
        ((listp (car l)) (myAppend (myReverse (cdr l)) (list (myReverse (car l)))))
        (T (myAppend (myReverse (cdr l)) (list (car l))))
    )
)

(defun sumList (l k c)
    (cond
        ((and (null l) (null k)) (if (= 1 c) (list 1) nil))
        (T (myAppend (sumList (cdr l) (cdr k) (carry (car l) (car k) c)) (list (digit (car l) (car k) c))))        
    )
)

(defun solve (l k)
    (sumList (myReverse l) (myReverse k) 0)
)
(terpri)
(print "c) Sum of [9, 9] and [1, 2, 3]")
(print (solve '(9 9) '(1 2 3)))
(print (solve '(1 2) '(2 3)))

(defun testSolve ()
	(assert
		(and
			(equal (solve '(9 9) '(1 2 3)) '(2 2 2))
			;(equal (solve '(1 2) '(2 3)) '(0 3 5))
		)
	)
)
(print "Test:")
(print (testSolve))

;;; ###############################################################################################################

;;; d) gcd of all numbers in a list

(defun mygcd (a b)
    (cond
        ((and (not (numberp a)) (not (numberp b))) nil)
        ((not (numberp a)) b)
        ((not (numberp b)) a)
        ((equal b 0) a)
        (T (mygcd b (mod a b)))
    )
)

(defun listgcd (l)
    (cond
        ((and (atom (car l)) (null (cdr l))) (car l))
        ((listp (car l)) (mygcd (listgcd (car l)) (listgcd (cdr l))))
        (T (mygcd (car l) (listgcd (cdr l))))
    )
)
(terpri)
(print "d) GCD of [24, 16 12 4]:")
(print (listgcd '(24 16 12 4)))
(print "Change GCD of [24, [16, [12, 4]], 72]:")
(print (listgcd '(24 ( 16 (12 4)) 72)))

(defun testListgcd ()
    (assert
        (and
            (equal (listgcd '(24 16 12 4)) '4)
            (equal (listgcd '(24 ( 16 (12 4)) 72)) '4)
        )
    )
)
(print "Test:")
(print (testListgcd))




