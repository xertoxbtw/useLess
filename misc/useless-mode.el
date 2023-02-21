;; -*- lexical-binding: t; -*-
(defun useless-indent-function ()
  (save-excursion
	(let ((indent-count 0)
		  (content (vconcat (buffer-substring 1 (- (line-beginning-position) 1)))))
	  (message content)
	  (beginning-of-line)
	  (indent-line-to (* indent-count tab-width)))))

(setq useless-keywords '("assign" "function" "include" "return" "while" "dotimes" "console.print" "console.println" "console.read" "console.readln" "add" "sub" "mul" "div" "mod" "if" "elif" "equal" "not" "greater" "less" "greater_equal" "less_equal" "string.format" "string.split" "string.replace" "file.read" "file.write" "list?" "string?" "number?" "list" "list.get" "list.set" "list.append" "list.do" "list.range" "list.copy" "map" "length" "internal.symbols" "tigr.window" "tigr.bitmap" "tigr.free" "tigr.closed" "tigr.update" "tigr.clear" "tigr.fill" "tigr.line" "tigr.rect" "tigr.fillRect" "tigr.circle" "tigr.fillCircle" "tigr.clip" "tigr.blit" "tigr.blitAlpha" "tigr.color" "tigr.print" "tigr.mouse" "tigr.keyDown" "tigr.keyHeld"))

(setq keywords-font-lock-spec
	  (cons (regexp-opt useless-keywords)
			(list 0 'font-lock-keyword-face 'keep)))

(setq brackets-font-lock-spec
	  (cons (regexp-opt '("(" ")" "[" "]" "{" "}"))
			(list 0 'font-lock-bracket-face 'keep)))
(setq comment-font-lock-spec
	  (cons "#.+"
			(list 0 'font-lock-comment-face)))

(setq useless-path "./useless")

(defun useless-execute-file ()
  (interactive "" useless-mode)
  (let* ((path (buffer-file-name))
		 (command (format "%s %s" useless-path path))
		 (result (shell-command-to-string command)))
	(get-buffer-create "useless-output")
	(pop-to-buffer "useless-output")
	(erase-buffer)
	(insert result)))

(defun useless-complete-symbol ()
  "Perform keyword completion on current symbol.
This uses `ido-mode' user interface for completion."
  (interactive)
  (let* (
		 (bds (bounds-of-thing-at-point 'symbol))
		 (p1 (car bds))
		 (p2 (cdr bds))
		 (current-sym
		  (if  (or (null p1) (null p2) (equal p1 p2))
			  ""
			(buffer-substring-no-properties p1 p2)))
		 result-sym)
	(when (not current-sym) (setq current-sym ""))
	(setq result-sym
		  (ido-completing-read "" useless-keywords nil nil current-sym ))
	(delete-region p1 p2)
	(insert result-sym)))

(define-derived-mode useless-mode nil "useLess"
  "Major mode for editing .ul files."
  (set (make-local-variable 'indent-line-function) #'useless-indent-function)
  (setq comment-start "#")

  (font-lock-add-keywords nil (list
							   keywords-font-lock-spec
							   brackets-font-lock-spec
							   comment-font-lock-spec)))


(provide 'useless-mode)
