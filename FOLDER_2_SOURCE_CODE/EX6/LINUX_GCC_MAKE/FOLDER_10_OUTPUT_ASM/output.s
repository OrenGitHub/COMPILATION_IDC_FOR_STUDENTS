main:

jal Label_0_main

Label_0_main:

	addi $fp,$sp,40

	j Label_7_Skip_This_Function_For_Now

Label_8_PrintPrimesInRange:

	li $t0,0

	li $t0,0

	j Label_9_Skip_This_Function_For_Now

Label_10_IsPrime:

	li $t0,0

	li $t0,0

	li $t0,-4

	add $t1,$fp,$t0

	li $t0,1

	sw $t0,0($t1)

	li $t0,-8

	add $t1,$fp,$t0

	li $t0,2

	sw $t0,0($t1)

	li $t1,2

	li $t0,8

	add $t2,$fp,$t0

	lw $t3,0($t2)

	li $t0,1

	sub $t2,$t3,$t0

	ble $t1, $t2, Label_11_for_loop

	bgt $t1, $t2, Label_12_exit_loop

Label_11_for_loop:

	li $t0,-12

	add $t1,$fp,$t0

	li $t0,2

	sw $t0,0($t1)

	li $t1,2

	li $t0,8

	add $t2,$fp,$t0

	lw $t3,0($t2)

	li $t0,1

	sub $t2,$t3,$t0

	ble $t1, $t2, Label_23_for_loop

	bgt $t1, $t2, Label_24_exit_loop

Label_23_for_loop:

	li $t0,-8

	add $t1,$fp,$t0

	lw $t2,0($t1)

	li $t0,-12

	add $t1,$fp,$t0

	lw $t3,0($t1)

	mul $t1,$t2,$t3

	li $t0,8

	add $t3,$fp,$t0

	lw $t2,0($t3)

	beq $t1, $t2, Label_52_T

	bne $t1, $t2, Label_53_F

Label_52_T:

	li $t0,1

	addi $t1,$t0,0

	j Label_54_END

Label_53_F:

	li $t0,0

	addi $t1,$t0,0

	j Label_54_END

Label_54_END:

	li $t0,0

	bne $t1, $t0, Label_35_if_taken

	beq $t1, $t0, Label_36_if_not_taken

Label_35_if_taken:

	li $t0,-4

	add $t1,$fp,$t0

	li $t0,0

	sw $t0,0($t1)

Label_36_if_not_taken:

	li $t0,-12

	add $t1,$fp,$t0

	li $t0,-12

	add $t2,$fp,$t0

	lw $t3,0($t2)

	li $t0,1

	add $t2,$t3,$t0

	sw $t2,0($t1)

	li $t0,-12

	add $t2,$fp,$t0

	lw $t1,0($t2)

	li $t0,8

	add $t2,$fp,$t0

	lw $t3,0($t2)

	li $t0,1

	sub $t2,$t3,$t0

	ble $t1, $t2, Label_23_for_loop

	bgt $t1, $t2, Label_24_exit_loop

Label_24_exit_loop:

	li $t0,-8

	add $t1,$fp,$t0

	li $t0,-8

	add $t2,$fp,$t0

	lw $t3,0($t2)

	li $t0,1

	add $t2,$t3,$t0

	sw $t2,0($t1)

	li $t0,-8

	add $t2,$fp,$t0

	lw $t1,0($t2)

	li $t0,8

	add $t2,$fp,$t0

	lw $t3,0($t2)

	li $t0,1

	sub $t2,$t3,$t0

	ble $t1, $t2, Label_11_for_loop

	bgt $t1, $t2, Label_12_exit_loop

Label_12_exit_loop:

	li $t0,-4

	add $t2,$fp,$t0

	lw $t1,0($t2)

	addi $v0,$t1,0

	li $t0,0

	li $t0,0

Label_9_Skip_This_Function_For_Now:

	li $t0,-4

	add $t1,$fp,$t0

	li $t0,8

	add $t3,$fp,$t0

	lw $t2,0($t3)

	sw $t2,0($t1)

	li $t0,8

	add $t2,$fp,$t0

	lw $t1,0($t2)

	li $t0,12

	add $t3,$fp,$t0

	lw $t2,0($t3)

	ble $t1, $t2, Label_65_for_loop

	bgt $t1, $t2, Label_66_exit_loop

Label_65_for_loop:

	li $t0,0

	bne $v0, $t0, Label_87_if_taken

	beq $v0, $t0, Label_88_if_not_taken

Label_87_if_taken:

Label_88_if_not_taken:

	li $t0,-4

	add $t1,$fp,$t0

	li $t0,-4

	add $t2,$fp,$t0

	lw $t3,0($t2)

	li $t0,1

	add $t2,$t3,$t0

	sw $t2,0($t1)

	li $t0,-4

	add $t2,$fp,$t0

	lw $t1,0($t2)

	li $t0,12

	add $t3,$fp,$t0

	lw $t2,0($t3)

	ble $t1, $t2, Label_65_for_loop

	bgt $t1, $t2, Label_66_exit_loop

Label_66_exit_loop:

	li $t0,0

	li $t0,0

Label_7_Skip_This_Function_For_Now:

	li $v0,10

	syscall
Label_1_AllocateRecord:

Label_2_AllocateArray:

Label_3_PrintInt:

	lw $a0,0($sp)

	li $v0,1

	syscall

	li $a0,32

	li $v0,11

	syscall

	jr $ra

Label_4_Access_Violation:

	li $a0,65

	li $v0,11

	syscall

	li $a0,99

	li $v0,11

	syscall

	li $a0,99

	li $v0,11

	syscall

	li $a0,101

	li $v0,11

	syscall

	li $a0,115

	li $v0,11

	syscall

	li $a0,115

	li $v0,11

	syscall

	li $a0,32

	li $v0,11

	syscall

	li $a0,86

	li $v0,11

	syscall

	li $a0,105

	li $v0,11

	syscall

	li $a0,111

	li $v0,11

	syscall

	li $a0,108

	li $v0,11

	syscall

	li $a0,97

	li $v0,11

	syscall

	li $a0,116

	li $v0,11

	syscall

	li $a0,105

	li $v0,11

	syscall

	li $a0,111

	li $v0,11

	syscall

	li $a0,110

	li $v0,11

	syscall

	li $v0,10

	syscall

