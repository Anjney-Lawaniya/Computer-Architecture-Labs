# max of a set
.text
	main: 
	 addi $t0, $0, 7
	 sw $t0, 0($s0)
	 addi $t0, $0, 2
	 sw $t0, 1($s0)
	 addi $t0, $0, 103
	 sw $t0, 2($s0)
	 addi $t0, $0, 15
	 sw $t0, 3($s0)
	 addi $t0, $0, 4
	 sw $t0, 4($s0)
	 
	 addi $t2, $0, 5	# limit
	 addi $t1, $0, 0	# counter
	 lw $s0, 0($s0)	# first value
	loop:
		slt $t4, $t1, $t2
		beq $t4, $0, exit
		lw $t3, 0($t1)
		slt $t4, $s0, $t3  
		beq $t4, $0, skip
		add $s0, $0, $t3
	skip:
		addi $t1, $t1, 1
		j loop
	exit:
		sw $s0, 20($0)
