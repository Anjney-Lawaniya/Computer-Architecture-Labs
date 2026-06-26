# task 2
.data
	input1: .asciiz "Enter first value: \n"
	input2: .asciiz "Enter second value: \n"
	
.text
	main: 
		la $a0, input1
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		move $s0, $v0
		
		la $a0, input2
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		move $s1, $v0
	
		add $t2, $0, $s1	# limit
		add $t0, $0, $s0	# start/iterator
		
		loop:
			slt $t1, $t2, $t0
			bne $t1, $0, doTheThing
			add $s2, $s2, $t0
			addi $t0, $t0, 1
			j loop
		doTheThing:
			li $v0, 1
			move $a0, $s2
			syscall
	exit: 
		li $v0, 10
		syscall
