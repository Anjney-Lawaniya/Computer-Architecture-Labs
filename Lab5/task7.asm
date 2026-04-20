.include "task7_macro_custom.asm"
.include "macro_print_str.asm"

.text
	main:
		print_string("Enter an integer to get reverse countdown: ")

    	li $v0, 5
    	syscall
    	move $t0, $v0

    	print_reverse_countdown($t0)

    	end			# taken form macro file
		
