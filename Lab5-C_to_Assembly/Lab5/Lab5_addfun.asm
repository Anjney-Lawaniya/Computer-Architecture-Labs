		.data
A:	.word 12, 34, 67, 1, 45, 90, 11, 33, 67, 19
	
	.text
main:
	la $s7, A
	li $s0, 0 #i
	li $s1, 0 #res
	li $s6, 9
	
loop:
	sll $t0, $s0, 2
	add $t0, $t0, $s7
	lw $a0, 0($t0)
	lw $a1, 4($t0)
	jal addfun
	add $s1, $s1, $v0
	addi $s0, $s0, 2
	bgt $s0, $s6, done
	j loop

done:	
	li $v0,10
	syscall
	
addfun:
	add $v0, $a0, $a1
	jr $ra
