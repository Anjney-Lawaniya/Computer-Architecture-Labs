#C Program
	#int sum(int a, int b , int c, int d, int e, int f){
	#	return (a+b+c+d+e+f);
	#}
#	int main(){
#		int a = 1, b = 2, c = 3, d = 4, d = 5, e = 5, f = 6;
	#	int y = sum(a,b,c,d,e,f);
	#}

.data
	a:
	b:
	c:
	d:
	e:
	f:
.text
	main:
		addi $sp, $sp, -4
		sw $ra, 0($sp)
		li $a0, 1
		li $a1, 2
		li $a2, 3
		li $a3, 4
		#Rest go in stack
		addi $sp, $sp, -8
		li $t0, 5
		sw $t0, 4($sp)
		li $t0, 6
		sw $t0, 0($sp)
		#---------------
		jal sum
		addiu $sp, $sp, 8
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		move $s0, $v0	#result
		li $v0, 10
		syscall
	
	sum:
		add $t0, $a0, $0
		add $t0, $t0, $a1
		add $t0, $t0, $a2
		add $t0, $t0, $a3
		# rest getting from stack
		lw $t1, 4($sp)
		add $t0, $t0, $t1
		lw $t1, 0($sp)
		add $t0, $t0, $t1
		move $v0, $t0
		jr $ra