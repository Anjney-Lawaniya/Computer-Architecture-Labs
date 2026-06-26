.data
  Array1: .word  11, 2,3,4,5,6,7,8,9
  Array2: .word  1, 21,13,41,15,16,17,18,19
  nos   : .word 10, 11
  res: .space 200  
 .text
 la $t0, Array2
 la $t0, res
 li $t1, 1
 li $t2, 1
 li $a0, 50
 L1:
 sw $t1, 0($t0)
 addu $t3, $t1, $t2
 move $t1, $t2
 move $t2, $t3
 addiu $t0, $t0, 4
 addiu $a0, $a0, -1
bne $a0, $zero, L1
addiu   $v0, $0, 10     
syscall     # Exit


