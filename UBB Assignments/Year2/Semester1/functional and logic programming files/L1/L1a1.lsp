;;; a) function to determine the nth element of a list

(defun n_elem (L n)
	(cond
		((null L) NIL)
		((= n 1) (car L))
		(T (n_elem (cdr L) (- n 1)))
	)
)
(print (n_elem '(1 2 3 7) '4))
(print (n_elem '(1 2 3 4) '5))
(terpri)

;;; b) atom E is member of nonlinear list

(defun check_member (L e)
	(cond
		((null L) NIL)
		((listp (car l)) (check_member (car L) e)) ; go in sublist
		((and (atom (car l)) (= (car l) e)) T) ; found element in list
		(T (check_member (cdr L) e)) ; keep searching
	)
)
(print (check_member '(1 2 3) '3))
(print (check_member '(1 (2 3)) '3))
(print (check_member '(1 (2 3)) '4))
(terpri)

; c) make list of all sublists

(defun allSublists (L)
  (cond
    ((atom L) nil)
    (T (apply 'append (list L) (mapcar 'allSublists L)))
  )
)
(print (allSublists '(1 (2 3 (4 5)) (6 7))))
(terpri)

; d) linear list to set

(defun make_set (L)
	(cond
		((null L) NIL)
		((check_member (cdr L) (car L)) (make_set (cdr L)))
		(T (cons (car L) (make_set (cdr L))))
	)
)
(print (make_set '(1 2 3 2)))
(print (make_set '(1 2 3)))
(print (make_set '(1 1 1)))
