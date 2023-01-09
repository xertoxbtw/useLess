;; -*- lexical-binding: t; -*-
(defun useless-indent-function ()
  (save-excursion
	(let ((indent-count 0)
		  (content (buffer-substring 1 (- (line-beginning-position) 1))))
	  (dotimes (i (- (length content) 1))
		(if (and (> i 0) (< i (length content)))
			(let ((current (substring content (+ i 1) (+ i 2))))
			  (if (equal current "{")
				  (setq indent-count (+ indent-count 1))
				(if (equal current "}")
					(setq indent-count (- indent-count 1)))))))

	  (beginning-of-line)
	  (indent-line-to (* indent-count tab-width)))))

(setq keywords-font-lock-spec
	  (cons (regexp-opt '("assign" "console.println" "function"))
			(list 0 'font-lock-keyword-face 'keep)))

(setq brackets-font-lock-spec
	  (cons (regexp-opt '("(" ")" "[" "]" "{" "}"))
			(list 0 'font-lock-bracket-face 'keep)))

(setq comment-font-lock-spec
	  (cons "#.+"
			(list 0 'font-lock-comment-face)))

(define-derived-mode useless-mode nil "useLess"
  "Major mode for editing .ul files."
  (set (make-local-variable 'indent-line-function) #'useless-indent-function)
  (setq comment-start "#")
  (font-lock-add-keywords nil (list
							   keywords-font-lock-spec
							   brackets-font-lock-spec
							   comment-font-lock-spec)))

(provide 'useless-mode)
