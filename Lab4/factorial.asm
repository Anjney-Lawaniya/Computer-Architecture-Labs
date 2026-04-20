#C program
	#int fact(int n){
	#	if(n <= 1){return n;}
		
	#	return n*fact(n-1);
#	}
	#int main(){
	#	int n;
	#	int y = fact(n);
	#	return y;
	#}
	
.text
	main:
		addi $sp, $sp, -4
		sw $ra, 0($sp)
		addi $a0, $0, 5		# User's Input
		jal fact
		move $s0, $v0
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		
		li $v0, 10
		syscall
		
	fact:
		add $t0, $0, 2
		#Base Case
		slt $t1, $a0, $t0
		beq $t1, 1, end_fact
		#Otherwise perform operation
		addi $sp, $sp, -4
		sw $ra, 0($sp)
		addi $a0, $a0, -1
		jal fact
		#Now $v0 contains answer, we just gotta multiply it my $a0 og value, which is in $s1
		addi $a0, $a0, 1
		mult $a0, $v0
		mflo $t3
		add $v0, $0, $t3
		#Restore
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
		
		end_fact:
			add $v0, $0, $a0
			jr $ra
		
		
		
		
		