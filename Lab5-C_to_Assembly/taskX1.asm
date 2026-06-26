# f = g + A[h + 2*i]
.data
	f: .word 0
	g: .word 3
	h: .word 1
	i: .word 2
	A: .word 1,2,3,4,5,6,7,8,9,10
.text
	lw $s1, g        # g
    lw $s2, h        # h
    lw $s3, i        # i
    la $s6, A
	
	sll $t0, $s3, 1
	add $t0, $t0, $s2
	sll $t0, $t0, 2
	add $t0, $t0, $s6
	lw $t1, 0($t0)
	add $s0, $s1, $t1
	
	li $v0, 10
	syscall