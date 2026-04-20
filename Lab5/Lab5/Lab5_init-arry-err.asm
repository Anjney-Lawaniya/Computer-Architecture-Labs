.data
     mydata: .word 1,2,3
     str:  .asciiz " Array initialized "
     final: .word 1
.text
      addi $s0, $0, 0    
 	  # addi $s1, $0, 0 	# ----> No need for this, later I am storing myData address in $s1  
	  addi $s2, $0, 10  
	  la $s1, mydata
	loop:  beq $s0, $s2, exit   	# $s1 replaced with $s0
	  sw  $s0, 0($s1)				# $s1 replaced with $s0
	  addi $s1, $s1, 4    			# $s0 replaced with $s1
	  add  $s0, $s0, 1				# $s1 replaced with $s0
	  j loop	
	  add  $a0, $s1, $0  
	  li $v0 , 4
          #add  $a0, $v0,$0      
     exit:
          li $v0, 10            
	  syscall


    
