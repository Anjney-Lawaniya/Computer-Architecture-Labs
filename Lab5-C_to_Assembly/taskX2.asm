.text
	main:
		li $a0, 5
		jal fact
		sw $v0, 0x10010000
		li $v0, 10
		syscall
	fact:
		addi $sp, $sp, -8
		sw $ra, 4($sp)
		sw $a0, 0($sp)
		li $t0, 1
		ble $a0, $t0, base_case
		addi $a0, $a0, -1
		jal fact
		lw $a0, 0($sp)
		mul $v0, $a0, $v0
		j end_fact
	base_case:
		li $v0, 1
	end_fact:
		lw $ra, 4($sp)
		addi $sp, $sp, 8
		jr $ra
