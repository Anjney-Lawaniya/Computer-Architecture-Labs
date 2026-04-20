.data
	result: .word 0

.text
	main:
  	  	li   $a0, 6        # argument n = 5
    	jal  fact          # call fact(5)
    	sw   $v0, result   # store result (120)

   	 	li   $v0, 10       # exit
    	syscall


	# int fact(int n)
	fact:
    	addi $sp, $sp, -8  # create stack frame
    	sw   $ra, 4($sp)  # save return address
    	sw   $a0, 0($sp)  # save n

    	li   $t0, 1
   	 	ble  $a0, $t0, base_case

    	addi $a0, $a0, -1 # n = n - 1
    	jal  fact         # recursive call

    	lw   $a0, 0($sp)  # restore n
    	mul  $v0, $a0, $v0  # n * fact(n-1)
    	j    end_fact

	base_case:
    	li   $v0, 1       # return 1

	end_fact:
    	lw   $ra, 4($sp)  # restore return address
    	addi $sp, $sp, 8  # pop stack frame
    	jr   $ra          # return
