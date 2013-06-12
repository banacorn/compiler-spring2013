.data
    a:		.float 0.0
.text
main:
    sw $ra, 0($sp)
    sw $fp, -4($sp)
    add $fp, $sp, -4
    add $sp, $sp, -8
    lw $2, main_framesize
    sub $sp, $sp, $2
    sw $8, 32($sp)
    sw $9, 28($sp)
    sw $10, 24($sp)
    sw $11, 20($sp)
    sw $12, 16($sp)
    sw $13, 12($sp)
    sw $14, 8($sp)
    sw $15, 4($sp)
main_begin:
    li $v0, 5
    syscall
    move $8, $v0
    sw $8, -4($fp)
while_0:
    lw $9, -4($fp)
    move $t0, $9
    beqz $t0, while_0_exit
    li $v0, 4
    la $a0, m0
    syscall
    li $v0, 4
    la $a0, m1
    syscall
    lw $10, -4($fp)
    li $11, 1
    sub $12, $10, $11
    sw $12, -4($fp)
    j while_0
while_0_exit:
main_end:
main_epilogue:
    lw $8, 32($sp)
    lw $9, 28($sp)
    lw $10, 24($sp)
    lw $11, 20($sp)
    lw $12, 16($sp)
    lw $13, 12($sp)
    lw $14, 8($sp)
    lw $15, 4($sp)
    lw $ra, 4($fp)
    add $sp, $fp, 4
    lw $fp, 0($fp)
    li $v0, 10
    syscall
.data
    main_framesize: .word 36
    m1: .asciiz "\n"
    m0: .asciiz "!!"
