.data
	data1: .byte 1,2,3,4,5,6
	#vowels: .byte 'a', 'e', 'i', 'o', 'u'
	#pow2: .word 1,2,4,8,16,32,64,128
	myWord: .word 0X12345678
	
	#Sequences like arrays and strings, have lowest address on the leftmost side.
	#Words standing alone have lowest address on the rightmost side (the Least significant byte).

.text
	main:
		li $v0, 1
		la $t0, data1  # base Address
		li $t1, 6      # Number of elements
		li $t2, 0	   # first index
	
	loop :
		la $a0, 0($t2)
		syscall
	
		addi $t0, $t0, 1
		addi $t2, $t2, 1
		blt $t2, $t1, loop  # if t2 < t1, goto loop
	
	exit:
		li $v0, 10
		syscall
