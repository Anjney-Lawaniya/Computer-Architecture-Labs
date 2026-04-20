.data
	msg1: .asciiz "Enter the first number: "
	msg2: .asciiz "\nEnter the second: "
	result: .asciiz "\nThe result of addition is: "
	
.text
	main:
		li $v0, 4    	# Taking input number 1
		la $a0, msg1
		syscall
		li $v0, 5
		syscall
		move $t1, $v0
		
		#Taking input number 2
		li $v0, 4
		la $a0, msg2
		syscall
		li $v0, 5
		syscall
		move $t2, $v0
		
		# Result
		add $t3, $t1, $t2
		li $v0, 4
		la $a0, result
		syscall
		li $v0, 1
		move $a0, $t3
		syscall
		
	exit:
		li $v0, 10
		syscall
		
		
		
		
		
