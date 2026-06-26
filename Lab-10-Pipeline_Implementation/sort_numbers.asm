addi $s7, $0, 9
loop1: addi $s6, $0, 0
add $s5, $0, $0
loop2: lw $s0, 0($s6)
lw $s1, 4($s6)
slt $s2, $s0, $s1
beq $s2, $0, swap
j next
swap: add $t0, $0, $s0
add $s0, $0, $s1
add $s1, $0, $t0
next: sw $s0, 0($s6)
sw $s1, 4($s6)
addi $s5, $s5, 1
addi $s6, $s6, 4
beq $s5, $s7, cont
j loop2
cont: subi $s7, $s7, 1
beq $s7, $0, stop
j loop1
stop: exit