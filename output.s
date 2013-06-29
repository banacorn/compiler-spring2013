.data
.text
fac_entry:
    # prologue
    sw $ra, 0($sp)
    sw $fp, -4($sp)
    add $fp, $sp, -4
    add $sp, $sp, -8
    lw $2, fac_framesize
    sub $sp, $sp, $2
    # save floating point
    s.s $f4, 92($sp)
    s.s $f6, 88($sp)
    s.s $f8, 84($sp)
    s.s $f10, 80($sp)
    s.s $f16, 76($sp)
    s.s $f18, 72($sp)
    # save integers
    sw $8, 68($sp)
    sw $9, 64($sp)
    sw $10, 60($sp)
    sw $11, 56($sp)
    sw $12, 52($sp)
    sw $13, 48($sp)
    sw $14, 44($sp)
    sw $15, 40($sp)
fac_begin:
    # variable reference
    s.s $f4, 4($sp)
    lw $16, 4($sp)
    # write
    li $v0, 2
    mov.s $f12, $f4
    syscall
    # variable reference
    s.s $f6, 4($sp)
    lw $16, 4($sp)
    # Int const
    li $8, 1
    # type coersion Int => Float
    # Int -> Float conversion 
    mtc1 $8, $f8
    cvt.s.w $f8, $f8
    # addition
    add.s $f10, $f6, $f8
    # return
    mov.s $f0, $f10
    j fac_end
fac_end:
    # eiplogue
fac_epilogue:
    # save floating point
    l.s $f4, 92($sp)
    l.s $f6, 88($sp)
    l.s $f8, 84($sp)
    l.s $f10, 80($sp)
    l.s $f16, 76($sp)
    l.s $f18, 72($sp)
    # load integers
    lw $8, 68($sp)
    lw $9, 64($sp)
    lw $10, 60($sp)
    lw $11, 56($sp)
    lw $12, 52($sp)
    lw $13, 48($sp)
    lw $14, 44($sp)
    lw $15, 40($sp)
    lw $ra, 4($fp)
    add $sp, $fp, 4
    lw $fp, 0($fp)
    jr $ra
.data
    fac_framesize: .word 92
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
    s.s $f4, 92($sp)
    s.s $f6, 88($sp)
    s.s $f8, 84($sp)
    s.s $f10, 80($sp)
    s.s $f16, 76($sp)
    s.s $f18, 72($sp)
    # save integers
    sw $8, 68($sp)
    sw $9, 64($sp)
    sw $10, 60($sp)
    sw $11, 56($sp)
    sw $12, 52($sp)
    sw $13, 48($sp)
    sw $14, 44($sp)
    sw $15, 40($sp)
main_begin:
    # Float const
    li.s $f16, 5.000000
    # save parameters
    sw $23, 36($sp)
    sw $22, 32($sp)
    sw $21, 28($sp)
    sw $20, 24($sp)
    sw $19, 20($sp)
    sw $18, 16($sp)
    sw $17, 12($sp)
    sw $16, 8($sp)
    # moving parameters
    s.s $f16, 4($sp) 
    lw $16, 4($sp) 
    # function call
    jal fac_entry
    lw $23, 36($sp)
    lw $22, 32($sp)
    lw $21, 28($sp)
    lw $20, 24($sp)
    lw $19, 20($sp)
    lw $18, 16($sp)
    lw $17, 12($sp)
    lw $16, 8($sp)
    mov.s $f18, $f0
main_end:
    # eiplogue
main_epilogue:
    # save floating point
    l.s $f4, 92($sp)
    l.s $f6, 88($sp)
    l.s $f8, 84($sp)
    l.s $f10, 80($sp)
    l.s $f16, 76($sp)
    l.s $f18, 72($sp)
    # load integers
    lw $8, 68($sp)
    lw $9, 64($sp)
    lw $10, 60($sp)
    lw $11, 56($sp)
    lw $12, 52($sp)
    lw $13, 48($sp)
    lw $14, 44($sp)
    lw $15, 40($sp)
    lw $ra, 4($fp)
    add $sp, $fp, 4
    lw $fp, 0($fp)
    li $v0, 10
    syscall
.data
    main_framesize: .word 92
.data
