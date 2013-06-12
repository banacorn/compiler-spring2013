.data
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
    li $v0, 4
    la $a0, m0
    syscall
    li $v0, 5
    syscall
    move $8, $v0
    sw $8, -4($fp)
while_0:
    lw $9, -4($fp)
    li $10, 0
    sgt $11, $9, $10
    move $t0, $11
    beqz $t0, while_0_exit
    lw $12, -4($fp)
    li $13, 2
    div $14, $12, $13
    li $15, 1
    sgt $8, $14, $15
    move $t0, $8
    beqz $t0, if_else_0_else
    li $v0, 4
    la $a0, m1
    syscall
    j if_else_0_exit
if_else_0_else:
    li $v0, 4
    la $a0, m2
    syscall
if_else_0_exit:
    lw $9, -4($fp)
    li $10, 1
    sub $11, $9, $10
    sw $11, -4($fp)
    j while_0
while_0_exit:
    li $12, 0
    move $v0, $12
    j main_end
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
.data
    m2: .asciiz "lower"
    m1: .asciiz "greater"
    m0: .asciiz "Loop index:"
