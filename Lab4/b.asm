.data
	msg: .asciiz "Hello"
	
.text
	main:
		la $a0, msg
		li $v0, 4
		syscall
		
	exit:
		li $v0, 10
		syscall
