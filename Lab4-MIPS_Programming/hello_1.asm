.data
	msg : .asciiz "Hello, World\n"
	msg2 : .asciiz "Putting to a test\n"
	
.text
	main:
	#print string
	li $v0, 4
	la $a0, msg
	syscall
	
	la $t0, msg2
	move $a0, $t0
	syscall
	
	#exit program
	li $v0, 10
	syscall
