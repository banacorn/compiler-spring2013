.data
.text
main:
    # prologue
    sw $ra, 0($sp)
    sw $fp, -4($sp)
    add $fp, $sp, -4
    add $sp, $sp, -8
    lw $2, main_framesize
    sub $sp, $sp, $2
    # save floating point
    s.s $f4, 120($sp)
    s.s $f6, 116($sp)
    s.s $f8, 112($sp)
    s.s $f10, 108($sp)
    s.s $f12, 104($sp)
    s.s $f14, 100($sp)
    s.s $f16, 96($sp)
    s.s $f18, 92($sp)
    # save integers
    sw $8, 88($sp)
    sw $9, 84($sp)
    sw $10, 80($sp)
    sw $11, 76($sp)
    sw $12, 72($sp)
    sw $13, 68($sp)
    sw $14, 64($sp)
    sw $15, 60($sp)
main_begin:
    # Int const
    li $8, 9
    # Int const initialization
    sw $8, -404($fp)
    # Int const
    li $9, 9
    # Int const initialization
    sw $9, -408($fp)
    # while
while_1_0:
    # variable reference
    lw $10, -404($fp)
    # Int const
    li $11, 0
    # type coersion Int => Float
    # relational operator
    sge $12, $10, $11
    move $t0, $12
    beqz $t0, while_1_0_exit
    # while
while_2_0:
    # variable reference
    lw $13, -408($fp)
    # Int const
    li $14, 0
    # type coersion Int => Float
    # relational operator
    sge $15, $13, $14
    move $t0, $15
    beqz $t0, while_2_0_exit
    # variable reference
    lw $16, -404($fp)
    # variable reference
    lw $17, -408($fp)
    # adding up offset
    li $18, 0
    add $18, $18, $16
    li $19, 10
    mul $18, $18, $19
    add $18, $18, $17
    li $19, 4
    mul $18, $18, $19
    # variable reference
    lw $8, -404($fp)
    # Int const
    li $9, 10
    # type coersion Int => Float
    # multiplication
    mul $10, $8, $9
    # variable reference
    lw $11, -408($fp)
    # type coersion Int => Float
    # addition
    add $12, $10, $11
    # assignment
    sub $18, $fp, $18
    addi $18, $18, -4
    sw $12, 0($18)
    # variable reference
    lw $13, -404($fp)
    # variable reference
    lw $14, -408($fp)
    # adding up offset
    li $15, 0
    add $15, $15, $13
    li $16, 10
    mul $15, $15, $16
    add $15, $15, $14
    li $16, 4
    mul $15, $15, $16
    # variable reference
    sub $15, $fp, $15
    addi $15, $15, -4
    lw $17, 0($15)
    # write
    li $v0, 1
    move $a0, $17
    syscall
    # string literal
    # write
    li $v0, 4
    la $a0, m0
    syscall
    # variable reference
    lw $18, -408($fp)
    # Int const
    li $19, 1
    # type coersion Int => Float
    # subtraction
    sub $8, $18, $19
    # assignment
    sw $8, -408($fp)
    j while_2_0
while_2_0_exit:
    # string literal
    # write
    li $v0, 4
    la $a0, m1
    syscall
    # variable reference
    lw $9, -404($fp)
    # Int const
    li $10, 1
    # type coersion Int => Float
    # subtraction
    sub $11, $9, $10
    # assignment
    sw $11, -404($fp)
    # Int const
    li $12, 9
    # assignment
    sw $12, -408($fp)
    j while_1_0
while_1_0_exit:
main_end:
    # eiplogue
main_epilogue:
    # save floating point
    l.s $f4, 120($sp)
    l.s $f6, 116($sp)
    l.s $f8, 112($sp)
    l.s $f10, 108($sp)
    l.s $f12, 104($sp)
    l.s $f14, 100($sp)
    l.s $f16, 96($sp)
    l.s $f18, 92($sp)
    # load integers
    lw $8, 88($sp)
    lw $9, 84($sp)
    lw $10, 80($sp)
    lw $11, 76($sp)
    lw $12, 72($sp)
    lw $13, 68($sp)
    lw $14, 64($sp)
    lw $15, 60($sp)
    lw $ra, 4($fp)
    add $sp, $fp, 4
    lw $fp, 0($fp)
    li $v0, 10
    syscall
.data
    main_framesize: .word 528
.data
    m1: .asciiz "\n"
    m0: .asciiz " "
