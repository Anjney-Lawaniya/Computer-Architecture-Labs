.data
	array1: .space 800
	array2: .space 400

.text
	la $s0, array1
	addi $t0, $0, 0
	addi $t1, $0, 0
	addi $s2, $0, 100
	
	loop:
		sll $t3, $t0, 2
		add $t3, $t3, $s0
		sw $t1, 0($t3)
		addi $t0, $t0, 1
		addi $t1, $t1, 2
		slt $t4, $t0, $s2
		bne $t4, $0, loop
	
	
		la $s1, array2
		addi $t0, $0, 0
		addi $t1, $0, 100
	
	doLoop:
		sll $t2, $t0, 2
		add $t3, $s0, $t2
		lw $t4, 0($t3)
	
		sll $t5, $t4, 2
		add $t6, $s0, $t5
		lw $t7, 0($t6)
	
		add $t8, $s1, $t2
		sw $t7, 0($t8)
	
		addi $t0, $t0, 1
		slt $t5, $t0, $t1
		bne $t5, $0, doLoop
	
exit:
	li $v0, 10
	syscall
