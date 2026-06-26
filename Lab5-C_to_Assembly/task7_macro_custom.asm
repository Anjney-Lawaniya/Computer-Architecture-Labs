.macro print_reverse_countdown(%n)
    move $t0, %n
loop:
    beq $t0, $zero, done
    li  $v0, 1
    move $a0, $t0
    syscall
    addi $t0, $t0, -1
    j loop
done:
.end_macro
