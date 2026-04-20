.data
	var1: .byte 3, -2, 'A'
	var2: .half 1,256, 0xfff
	var3: .word 0x3de1c74, 0xff
		  .align 3			# go to next multiple of 2^3
	str1: .asciiz "CS2206"
