# task 2
.data
	x: .word 2
	y: .word 7
	z: .word 6
	q: .word 2
.text
	main:
		lw $s1, x
		lw $s2, y
		lw $s3, z
		lw $s4, q
		
		sub $s3, $s3, $s4
		add $s2, $s2, $s3
		add $s1, $s1, $s2
	
	exit:
		li $v0, 10
		syscall
	
