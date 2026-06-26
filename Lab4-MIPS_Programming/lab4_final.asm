.data
	forInt: .asciiz "\nEnter an integer: \n"
	forFloat: .asciiz "\nEnter a float: \n"
	forDouble: .asciiz "\nEnter a double: \n"
	forString: .asciiz "\nEnter a string: \n"
	forChar: .asciiz "\nEnter a character: \n"
	
	buffer: .space 100
	
	filename: .asciiz "test.txt"
	filebuf:  .space  64
	
.text
	main:
		#int
		li $v0, 4		#Input
		la $a0, forInt
		syscall
		li $v0, 5		# Print
		syscall
		move $a0, $v0
		li $v0, 1
		syscall
	
		#float
		li $v0, 4
		la $a0, forFloat
		syscall
		li $v0, 6
		mov.s $f12, $f0
		li $v0, 2
		syscall
	
		#double
		li $v0, 4
		la $a0, forDouble
		syscall
		li $v0, 7
		syscall
		mov.d $f12, $f0
		li $v0, 3
		syscall
	
		#string
		li $v0, 4
		la $a0, forString
		syscall
		li $v0, 8
		la $a0, buffer
		li $a1, 100
		syscall
		li $v0, 4
		la $a0, buffer
		syscall
	
		#char
		li $v0, 4
		la $a0, forChar
		syscall
		li $v0, 12
		syscall
		move $a0, $v0
		li $v0, 11
		syscall
		
		#sbrk allocate 
		li $v0, 9
		li $a0, 32      
		syscall            

		move $s0, $v0      


		#read
		li $v0, 14
		move $a0, $s1    
		la $a1, filebuf     
		li $a2, 64         
		syscall

		#write
		li $v0, 15
		li $a0, 1      
		la $a1, filebuf    
		li $a2, 64          
		syscall
		
		#close
		# close the file
		li $v0, 16
		move $a0, $s1       # file descriptor
		syscall             # returns 0 in $v0


	exit:
		li $v0, 10
		syscall
		
	exit2:
		# exit with return code 0
		li $v0, 17
		li $a0, 0
		syscall

