.data
	value: .word 7
	result: .word 0
.text
	main:
		lw $s0, value
		move $s1, $s0
		sll $s0, $s0, 2
		add $s0, $s0, $s1
		sw $s0, result
		
	exit:
		li $v0, 10
		syscall