.data
A  : .word 0x23456789
B  : .word 0x23456789
Result: .word 
.text
	main:
	lw $s0, A
	lw $s1, B
	add $s3,$s0 $s1
	sw $s3, Result
	lb $s0, 1($1)
exit:	li $v0, 10
	syscall
