main:

jal Label_0_main

Label_0_main:

	addi $fp,$sp,40

	j Label_7_Skip_This_Function_For_Now

Label_8_PrintPrimesInRange:

	li $t0,4

	sub $t1,$sp,$t0

	addi $sp,$t1,0

	sw $ra,0($sp)

	li $t0,4

	sub $t1,$sp,$t0

	addi $sp,$t1,0

	sw $fp,0($sp)

	addi $fp,$sp,0

	li $t0,4

	sub $t1,$sp,$t0

	addi $sp,$t1,0

	j Label_9_Skip_This_Function_For_Now

Label_10_IsPrime:

	li $t0,4

	sub $t1,$sp,$t0

	addi $sp,$t1,0

	sw $ra,0($sp)

	li $t0,4

	sub $t1,$sp,$t0

	addi $sp,$t1,0

	sw $fp,0($sp)

	addi $fp,$sp,0

	li $t0,12

	sub $t1,$sp,$t0

	addi $sp,$t1,0

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

	addi $sp,$fp,0

	lw $t0,0($sp)

	addi $fp,$t0,0

	li $t0,4

	add $t1,$sp,$t0

	addi $sp,$t1,0

	lw $t0,0($sp)

	addi $ra,$t0,0

	li $t0,4

	add $t1,$sp,$t0

	addi $sp,$t1,0

	jr $ra

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

	addi $sp,$sp,-4

	sw $t0,0($sp)

	addi $sp,$sp,-4

	sw $t1,0($sp)

	addi $sp,$sp,-4

	sw $t2,0($sp)

	addi $sp,$sp,-4

	sw $t3,0($sp)

	addi $sp,$sp,-4

	sw $t4,0($sp)

	addi $sp,$sp,-4

	sw $t5,0($sp)

	addi $sp,$sp,-4

	sw $t6,0($sp)

	addi $sp,$sp,-4

	sw $t7,0($sp)

	li $t0,-4

	add $t2,$fp,$t0

	lw $t1,0($t2)

	addi $sp,$sp,-4

	sw $t1,0($sp)

	jal Label_10_IsPrime

	addi $sp,$sp,4

	lw $t7,0($sp)

	addi $sp,$sp,4

	lw $t6,0($sp)

	addi $sp,$sp,4

	lw $t5,0($sp)

	addi $sp,$sp,4

	lw $t4,0($sp)

	addi $sp,$sp,4

	lw $t3,0($sp)

	addi $sp,$sp,4

	lw $t2,0($sp)

	addi $sp,$sp,4

	lw $t1,0($sp)

	addi $sp,$sp,4

	lw $t0,0($sp)

	addi $sp,$sp,4

	li $t0,0

	bne $v0, $t0, Label_87_if_taken

	beq $v0, $t0, Label_88_if_not_taken

Label_87_if_taken:

	addi $sp,$sp,-4

	sw $t0,0($sp)

	addi $sp,$sp,-4

	sw $t1,0($sp)

	addi $sp,$sp,-4

	sw $t2,0($sp)

	addi $sp,$sp,-4

	sw $t3,0($sp)

	addi $sp,$sp,-4

	sw $t4,0($sp)

	addi $sp,$sp,-4

	sw $t5,0($sp)

	addi $sp,$sp,-4

	sw $t6,0($sp)

	addi $sp,$sp,-4

	sw $t7,0($sp)

	li $t0,-4

	add $t2,$fp,$t0

	lw $t1,0($t2)

	addi $sp,$sp,-4

	sw $t1,0($sp)

	jal Label_3_PrintInt

	addi $sp,$sp,4

	lw $t7,0($sp)

	addi $sp,$sp,4

	lw $t6,0($sp)

	addi $sp,$sp,4

	lw $t5,0($sp)

	addi $sp,$sp,4

	lw $t4,0($sp)

	addi $sp,$sp,4

	lw $t3,0($sp)

	addi $sp,$sp,4

	lw $t2,0($sp)

	addi $sp,$sp,4

	lw $t1,0($sp)

	addi $sp,$sp,4

	lw $t0,0($sp)

	addi $sp,$sp,4

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

	addi $sp,$fp,0

	lw $t0,0($sp)

	addi $fp,$t0,0

	li $t0,4

	add $t1,$sp,$t0

	addi $sp,$t1,0

	lw $t0,0($sp)

	addi $ra,$t0,0

	li $t0,4

	add $t1,$sp,$t0

	addi $sp,$t1,0

	jr $ra

Label_7_Skip_This_Function_For_Now:

	addi $sp,$sp,-4

	sw $t0,0($sp)

	addi $sp,$sp,-4

	sw $t1,0($sp)

	addi $sp,$sp,-4

	sw $t2,0($sp)

	addi $sp,$sp,-4

	sw $t3,0($sp)

	addi $sp,$sp,-4

	sw $t4,0($sp)

	addi $sp,$sp,-4

	sw $t5,0($sp)

	addi $sp,$sp,-4

	sw $t6,0($sp)

	addi $sp,$sp,-4

	sw $t7,0($sp)

	li $t0,100

	addi $sp,$sp,-4

	sw $t0,0($sp)

	li $t0,2

	addi $sp,$sp,-4

	sw $t0,0($sp)

	jal Label_8_PrintPrimesInRange

	addi $sp,$sp,8

	lw $t7,0($sp)

	addi $sp,$sp,4

	lw $t6,0($sp)

	addi $sp,$sp,4

	lw $t5,0($sp)

	addi $sp,$sp,4

	lw $t4,0($sp)

	addi $sp,$sp,4

	lw $t3,0($sp)

	addi $sp,$sp,4

	lw $t2,0($sp)

	addi $sp,$sp,4

	lw $t1,0($sp)

	addi $sp,$sp,4

	lw $t0,0($sp)

	addi $sp,$sp,4

	li $v0,10

	syscall
Label_1_AllocateRecord:

	lw $a0,0($sp)

	li $a1,4

	mul $a0,$a1,$a0

	li $v0,9

	syscall

	lw $a0,0($sp)

	li $a1,0

	li $a2,0

Label_1_Loop:

	bge $a1,$a0,Label_1_ExitLoop

	add $v1,$v0,$a2

	addi $a3,$sp,4

	add $a3,$a3,$a2

	lw $a3,0($a3)

	sw $a3,0($v1)

	addi $a1,$a1,1

	addi $a2,$a2,4

	j Label_1_Loop

Label_1_ExitLoop:

	jr $ra

Label_2_AllocateArray:

	lw $a0,0($sp)

	addi $a0,$a0,1

	li $a1,4

	mul $a0,$a1,$a0

	li $v0,9

	syscall

	lw $a0,0($sp)

	sw $a0,0($v0)

	li $a1,0

	li $a2,0

Label_2_Loop:

	bge $a1,$a0,Label_2_ExitLoop

	add $v1,$v0,$a2

	addi $v1,$v1,4

	lw $a3,4($sp)

	sw $a3,0($v1)

	addi $a1,$a1,1

	addi $a2,$a2,4

	j Label_2_Loop

Label_2_ExitLoop:

	jr $ra

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

