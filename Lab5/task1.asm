# task 1
.data
	array: .byte 1,2,3,4,5
	msg: .asciiz "Hello\n"
.text
	main:
		addi $s0, $s0, 2
		addi $s1, $s1, 3
		addi $s2, $s2, 4
		addi $s3, $s3, 5
		addi $s4, $s4, 4
		
		move $t0, $s0
		li $t1, 10
		la $t2, array
		nop
		# clear $t2
		not $t1, $s2
		neg $t0, $s2
		b next
		
		la $a0, msg
		li $v0, 4
		syscall
		
	next: 
		beqz $s1, exit
		bnez $zero, exit
		blt $s2, $s1, exit
		ble	$s2, $s1, exit
		bgt	$s1, $s2, exit
		bge $s1, $s2, exit
		mul $t0, $s2, $s3
		div	$t1, $s2, $s0
		rem	$t2, $s3, $s1
		seq $t1, $s2, $s4
		sne	$t2, $s2, $s3
	
	exit:
		li $v0, 10
		syscall