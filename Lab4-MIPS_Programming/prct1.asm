# basic jal
.text
	main:
	 addi $a0, $0, 2
	 addi $a1, $zero, 3
	 jal func
	 addi $s0, $v0, 0
	 j exit
	 func:
	 	add $v0, $a0, $a1
	 	jr $ra
	 exit: 