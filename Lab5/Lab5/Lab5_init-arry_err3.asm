.data
     mydata: .word 1,2,3
     str:  .asciiz " Array initialized "
     final: .word 1
.text
     addi $s0, $0, 0 
 	 # addi $s1, $0, 0    
	 addi $s2, $0, 10   
	 la $t1, mydata
	loop:  
	  #beq $s2, $t1, exit   	# ----> Error: comparing address and constant value
	  beq $s0, $s2, exit
	  sw  $s0, 0($t1)
	  addi $t1, $t1, 4	# 4, not 1
	  addi $s0, $s0, 1	# --> Missing line
	  j loop
	  add  $a0, $s1, $0 
	  li $v0 , 4     
     exit:
          li $v0, 10             
	  	  syscall


    
