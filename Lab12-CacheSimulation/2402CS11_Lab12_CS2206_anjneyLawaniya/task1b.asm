.data
	a: .space 400

.text
	la $s0, a
	addi $t0, $0, 0
	addi $s1, $0, 100
	
	oLoop:
		addi $t1, $0, 0
	
		iLoop:
			sll $t2, $t1, 2
			add $t3, $s0, $t2
			sw $t1, 0($t3)
	
			addi $t1, $t1, 1
			slt $t4, $t1, $s1
			bne $t4, $0, iLoop
	
		addi $t0, $t0, 1
		slt $t4, $t0, $s1
		bne $t4, $0, oLoop

exit:
	li $v0, 10
	syscall
