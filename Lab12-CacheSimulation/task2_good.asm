# int a[256], b[256], c[256];
# int n = 16;
# for(int i = 0; i < n; i++) {
#     for(int k = 0; k < n; k++) {
#         for(int j = 0; j < n; j++) {
#             c[i*n+j] = c[i*n+j]+a[i*n+k]*b[k*n+j];
#         }
#     }
# }

.data
	a: .space 1024
	b: .space 1024
	c: .space 1024

.text
	la $s0, a
	la $s1, b
	la $s2, c
	addi $s3, $0, 16
	
	addi $t0, $0, 0
	
oLoop:
	addi $t2, $0, 0
	
mLoop:
	addi $t1, $0, 0
	
iLoop:
	sll $t3, $t0, 6
	sll $t4, $t2, 2
	add $t5, $t3, $t4
	add $t5, $s0, $t5
	lw $t6, 0($t5)
	
	sll $t3, $t2, 6
	sll $t4, $t1, 2
	add $t5, $t3, $t4
	add $t5, $s1, $t5
	lw $t7, 0($t5)
	
	mult $t6, $t7
	mflo $t6
	
	sll $t3, $t0, 6
	sll $t4, $t1, 2
	add $t5, $t3, $t4
	add $t5, $s2, $t5
	lw $t7, 0($t5)
	
	add $t7, $t7, $t6
	sw $t7, 0($t5)
	
	addi $t1, $t1, 1
	slt $t3, $t1, $s3
	bne $t3, $0, iLoop
	
	addi $t2, $t2, 1
	slt $t3, $t2, $s3
	bne $t3, $0, mLoop
	
	addi $t0, $t0, 1
	slt $t3, $t0, $s3
	bne $t3, $0, oLoop
	
exit:
	li $v0, 10
	syscall
