.data
.text
add_entry:
    # prologue
    sw $ra, 0($sp)
    sw $fp, -4($sp)
    add $fp, $sp, -4
    add $sp, $sp, -8
    lw $2, add_framesize
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
add_begin:
    # variable reference
    mov.s $f4, $f20
    # variable reference
    mov.s $f6, $f22
    # type coersion Int => Float
    # addition
    add.s $f8, $f4, $f6
    # variable reference
    mov.s $f10, $f24
    # type coersion Int => Float
    # addition
    add.s $f12, $f8, $f10
    # variable reference
    move $8, $16
    # type coersion Int => Float
    # Int -> Float conversion 
    mtc1 $8, $f14
    cvt.s.w $f14, $f14
    # addition
    add.s $f16, $f12, $f14
    # variable reference
    move $9, $17
    # type coersion Int => Float
    # Int -> Float conversion 
    mtc1 $9, $f18
    cvt.s.w $f18, $f18
    # addition
    add.s $f4, $f16, $f18
    # return
    mov.s $f0, $f4
    j add_end
add_end:
    # eiplogue
add_epilogue:
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
    jr $ra
.data
    add_framesize: .word 120
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
    li $10, 1
    # Float const
    li.s $f6, 2.500000
    # Float const
    li.s $f8, 4.500000
    # Int const
    li $11, 5
    # Int const
    li $12, 6
    # save parameters
    s.s $f30, 56($sp)
    s.s $f28, 52($sp)
    s.s $f26, 48($sp)
    s.s $f24, 44($sp)
    s.s $f22, 40($sp)
    s.s $f20, 36($sp)
    sw $23, 32($sp)
    sw $22, 28($sp)
    sw $21, 24($sp)
    sw $20, 20($sp)
    sw $19, 16($sp)
    sw $18, 12($sp)
    sw $17, 8($sp)
    sw $16, 4($sp)
    # moving parameters
    mov.s $f20, $f10 
    mov.s $f22, $f6 
    mov.s $f24, $f8 
    move $16, $11 
    move $17, $12 
    # function call
    jal add_entry
    l.s $f30, 56($sp)
    l.s $f28, 52($sp)
    l.s $f26, 48($sp)
    l.s $f24, 44($sp)
    l.s $f22, 40($sp)
    l.s $f20, 36($sp)
    lw $23, 32($sp)
    lw $22, 28($sp)
    lw $21, 24($sp)
    lw $20, 20($sp)
    lw $19, 16($sp)
    lw $18, 12($sp)
    lw $17, 8($sp)
    lw $16, 4($sp)
    mov.s $f10, $f0
    # assignment
    s.s $f10, -4($fp)
    # variable reference
    l.s $f12, -4($fp)
    # write
    li $v0, 2
    mov.s $f12, $f12
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
    main_framesize: .word 124
.data
