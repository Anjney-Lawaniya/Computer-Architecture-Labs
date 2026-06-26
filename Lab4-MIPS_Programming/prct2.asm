# jal before midterm
.text
	li $a0, 5
	jal func
	j exit
	func:
		add $v0, $a0, $a0
		jr $ra
	exit: