(defun myMax(a b)
  (cond
    ((and (not (numberp a)) (not (numberp b))) nil)
    ((not (numberp b)) a)
    ((not (numberp a)) b)
    ((> a b) a)
    (t b)
  )
)


(defun findMax(l)
  (cond
    ((null l) nil)
	;((listp (car l)) (myMax (findMax (car l)) (findMax(cdr l))))
    (t (myMax (car l) (findMax (cdr l))))
  )
)
;(print (findMax '(1 4 2 7 5)))
;(terpri)


(defun treeDepthRec (tree level)
	(cond
		((atom tree) level)

		((listp tree) (apply #'findMax (list (mapcar #'(lambda (a) (treeDepthRec a (+ 1 level))) tree))))
	)
)

(defun treeDepth (tree) 
	(treeDepthRec tree 0)
)
(print "Depth of tree: (A (B (C)) (D) (E (F)))")
(print (treeDepth '(A (B (C)) (D) (E (F))))) ; => 3


(defun testTreeDepth ()
	(assert 
		(equal (treeDepth '()) '0)
		(equal (treeDepth '(A (B (C)) (D) (E (F)))) '3)
		(equal (treeDepth '(A (B (C (NEW NEW))) (D) (E (F)))) '4)
	)
)
(terpri)
(print "Test results:")
(print (testTreeDepth))


(defun treeDepthChanged (tree level minLvl)
	(cond
		((atom tree) level)
		((< level minLvl) (apply #'findMax (list (mapcar #'(lambda (a) (treeDepthChanged a level (- 1 minLvl))) tree))))
		(t (apply #'findMax (list (mapcar #'(lambda (a) (treeDepthChanged a (+ 1 level) minLvl)) tree))))
	)
)

(defun f (tree minLvl)
	(treeDepthChanged tree '0 minLvl)
)
(print "Tree Depth with min depth 1 for (A (B (C)) (D) (E (F))):")
(print (f '(A (B (C)) (D) (E (F)))'1))

(defun testTreeDepthChanged ()
	(assert
		(equal (f '(A (B (C)) (D) (E (F))) '1) '2)
		(equal (f '(A (B (C)) (D) (E (F))) '2) '1)
		(equal (f '(A (B (C)) (D) (E (F))) '4) 'nil)
	)
)
(terpri)
(print "Tests for change:")
(print (testTreeDepthChanged))
		