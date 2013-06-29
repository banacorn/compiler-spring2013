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
    li $8, 2
    # Int const
    li $9, 3
    # adding up offset
    li $10, 0
    add $10, $10, $8
    li $11, 10
    mul $10, $10, $11
    add $10, $10, $9
    li $11, 4
    mul $10, $10, $11
    # Int const
    li $12, 4
    # assignment
    sub $10, $fp, $10
    addi $10, $10, -4
    sw $12, 0($10)
    # Int const
    li $13, 2
    # Int const
    li $14, 3
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
    main_framesize: .word 520
.data
