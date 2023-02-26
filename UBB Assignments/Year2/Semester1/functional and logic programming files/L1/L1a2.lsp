; a) dot product of two vectors

(defun dot_product (a b)
	(cond
		((/= (length a) (length b)) NIL)
		((null a) 0)
		((null b) 0)
		(T (+ (* (car a) (car b)) (dot_product (cdr a) (cdr b))))
	)
)

(print (dot_product '(1 2 3) '(1 2 3)))
(print (dot_product '(1 2) '(1)))
(terpri)

; b) depth of a list

(defun list_depth (l c)
  (cond
    ((null l) c)
    ((listp (car l)) (max (list_depth (car l) (+ c 1)) (list_depth (cdr l) c)))
    (t (list_depth (cdr l) c))
  )
)


(print (list_depth '(1 2 3) '0))
(print (list_depth '(1 (2 3) 4 (1 (2 3 (4)))) '0))