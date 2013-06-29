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
    s.s $f12, 76($sp)
    s.s $f14, 72($sp)
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
    # read
    li $v0, 6
    syscall
    mov.s $f4, $f0
    # assignment
    s.s $f4, -4($fp)
    # Float const
    li.s $f6, 3.000000
    # assignment
    s.s $f6, -8($fp)
    # Float const
    li.s $f8, 6.000000
    # assignment
    s.s $f8, -12($fp)
    # variable reference
    l.s $f10, -4($fp)
    # Int const
    li $8, 3
    # type coersion Int => Float
    # Int -> Float conversion 
    mtc1 $8, $f12
    cvt.s.w $f12, $f12
    # multiplication
    mul.s $f14, $f10, $f12
    # variable reference
    l.s $f4, -8($fp)
    # Float const
    li.s $f6, 6.000000
    # type coersion Int => Float
    # division
    div.s $f8, $f4, $f6
    # type coersion Int => Float
    # addition
    add.s $f10, $f14, $f8
    # assignment
    s.s $f10, -4($fp)
    # variable reference
    l.s $f12, -4($fp)
    # write
    li $v0, 2
    mov.s $f12, $f12
    syscall
    # string literal
    # write
    li $v0, 4
    la $a0, m0
    syscall
main_end:
    # eiplogue
main_epilogue:
    # save floating point
    l.s $f4, 92($sp)
    l.s $f6, 88($sp)
    l.s $f8, 84($sp)
    l.s $f10, 80($sp)
    l.s $f12, 76($sp)
    l.s $f14, 72($sp)
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
    main_framesize: .word 104
.data
    m0: .asciiz "\n"
