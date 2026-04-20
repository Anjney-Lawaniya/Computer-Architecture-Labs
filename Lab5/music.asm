.data  
syscalls: 		.half 31, 31, 33, 33, 33, 33, 31, 31, 33, 33, 33, 33, 31, 31, 33, 33, 33, 33, 31, 31, 33, 33, 33, 33, 31, 31, 33, 33, 33, 33, 31, 31, 33, 33, 33, 33, 31, 31, 33, 33, 33, 33, 31, 31, 33, 33, 33, 33
notes: 			.half 79, 77, 75, 74, 72, 70, 68, 67, 79, 77, 75, 74, 72, 70, 68, 67, 79, 77, 75, 74, 72, 70, 68, 67, 79, 77, 75, 74, 72, 70, 68, 67, 79, 77, 75, 74, 72, 70, 68, 67, 79, 77, 75, 74, 72, 70, 68, 67
durs: 			.half 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500
instrums:		.half 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81
volumes:		.half 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20


inputString: .asciiz "Please enter playback speed between 1 and 5 \n"
volumeString: .asciiz "Please enter playback volume between 1 and 6 \n"
octaveString: .asciiz "Please enter an octave between 1 and 5, with 3 being default. \n"

.text
.globl main


.macro newnote (%sys, %note, %dur, %instrum, %volume)

move $v0, %sys		 #Syscall for midi
move $a0, %note		 #Note ID
move $a1, %dur		 #Duration in Miliseconds
move $a2, %instrum	 #Instrument ID
move $a3, %volume 	 #volume
syscall

.end_macro


main:   

readint:		#read integer from user input, stored in v0 and moved to s4

li $v0, 4
la $a0, inputString
syscall


li $v0, 5
syscall

move $s4, $v0 		#user's playback speed stored in $s4

li $v0, 4
la $a0, volumeString
syscall

li $v0, 5
syscall

move $s5, $v0		#user's volume level stored in $s5


li $v0, 4
la $a0, octaveString
syscall

li $v0, 5
syscall

move $t8, $v0		#user's octave level stored in $t8 (used as multiplier)


length:			#calculate length of the amount of notes, store in t7

li $v0, 31
la $t7, syscalls
la $t6, notes

sub $t7, $t6, $t7
srl $t7, $t7, 1


li $s0, 0
loop:			#loop through each of the notes until you reach the end, then terminate.
sll $s1, $s0, 1
lh $t0, syscalls($s1)
lh $t1, notes($s1)
lh $t2, durs($s1)
lh $t3, instrums($s1)
lh $t4, volumes($s1)

div $t2, $s4
mflo $t2

mult $t4, $s5
mflo $t4

li $t5, 12
mult $t8, $t5
mflo $t5
add $t1, $t1, $t5

newnote ($t0, $t1, $t2, $t3, $t4)


addi $s0, $s0, 1
bne $s0, $t7, loop


li $v0, 10
syscall
