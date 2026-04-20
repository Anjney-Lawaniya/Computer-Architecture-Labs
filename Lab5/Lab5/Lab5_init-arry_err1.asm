# ALREADY CORRECT
.data
    mydata: .word 1,2,3
    str:  .asciiz " Array initialized "
    final: .word 1

.text
    addi $s0, $0, 0        # argument i = 0
    # addi $s1, $0, 0      # asum = 0 (unused, left as-is)
    addi $s2, $0, 10       # loop counter
    la   $t1, mydata

loop:
    # beq $s2, $t1, exit  # ? ERROR: comparing counter with address
    beq $s2, $zero, exit  # ? FIX: compare counter with zero

    sw  $s0, 0($t1)

    # addi $t1, $t1, 1    # ? ERROR: .word needs 4-byte increment
    addi $t1, $t1, 4      # ? FIX: move to next word

    addi $s2, $s2, -1
    j loop

    # add  $a0, $s1, $0   # ? ERROR: unreachable (after jump)
    # li   $v0, 4         # ? ERROR: unreachable and no syscall

exit:
    la   $a0, str
    li   $v0, 4
    syscall

    li $v0, 10
    syscall
