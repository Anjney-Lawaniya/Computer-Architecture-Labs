# --- Part 1: Writing ASCII to Memory (Starting at 128) ---
addi $s0, $zero, 0x00400000     # Base Address = 128 (0x80)

# Storing "Anjney Lawaniya 2402CS11"
addi $t0, $zero, 65      # 'A'
sw   $t0, 0($s0)
addi $t0, $zero, 110     # 'n'
sw   $t0, 4($s0)
addi $t0, $zero, 106     # 'j'
sw   $t0, 2($s0)
addi $t0, $zero, 110     # 'n'
sw   $t0, 3($s0)
addi $t0, $zero, 101     # 'e'
sw   $t0, 4($s0)
addi $t0, $zero, 121     # 'y'
sw   $t0, 5($s0)
addi $t0, $zero, 32      # ' '
sw   $t0, 6($s0)
addi $t0, $zero, 76      # 'L'
sw   $t0, 7($s0)
addi $t0, $zero, 97      # 'a'
sw   $t0, 8($s0)
addi $t0, $zero, 119     # 'w'
sw   $t0, 9($s0)
addi $t0, $zero, 97      # 'a'
sw   $t0, 10($s0)
addi $t0, $zero, 110     # 'n'
sw   $t0, 11($s0)
addi $t0, $zero, 105     # 'i'
sw   $t0, 12($s0)
addi $t0, $zero, 121     # 'y'
sw   $t0, 13($s0)
addi $t0, $zero, 97      # 'a'
sw   $t0, 14($s0)
addi $t0, $zero, 50      # '2'
sw   $t0, 15($s0)
addi $t0, $zero, 52      # '4'
sw   $t0, 16($s0)
addi $t0, $zero, 48      # '0'
sw   $t0, 17($s0)
addi $t0, $zero, 50      # '2'
sw   $t0, 18($s0)
addi $t0, $zero, 67      # 'C'
sw   $t0, 19($s0)
addi $t0, $zero, 83      # 'S'
sw   $t0, 20($s0)
addi $t0, $zero, 49      # '1'
sw   $t0, 21($s0)
addi $t0, $zero, 49      # '1'
sw   $t0, 22($s0)

# --- Part 2: Finding the Sum ---
addi $s1, $zero, 0       # Sum = 0
addi $t1, $zero, 0       # i = 0
addi $t2, $zero, 23      # Limit = 23

sum_loop:
    beq  $t1, $t2, end     # If i == 23, jump to end
    add  $t3, $s0, $t1     # Addr = 128 + i
    lw   $t4, 0($t3)       # Load character
    add  $s1, $s1, $t4     # sum += char
    addi $t1, $t1, 1       # i++
    j    sum_loop          # Repeat

end:
    sw   $s1, 200($zero)   # Store final sum at a very safe address (200)