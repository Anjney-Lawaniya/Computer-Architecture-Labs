.macro print_reverse_countdown(%n)
.data
	number: .word %n
.text
	main:
		lw $t0, number
		loop:
			beq $t0, 0, exit
			li $v0, 1
			lw $a0, 0($t0)
			addi $t0, -1
			syscall
	exit:
		li $v0, 10
		syscall
.end_macro