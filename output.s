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
    s.s $f4, 88($sp)
    s.s $f6, 84($sp)
    s.s $f8, 80($sp)
    s.s $f10, 76($sp)
    s.s $f16, 72($sp)
    s.s $f18, 68($sp)
    # save integers
    sw $8, 64($sp)
    sw $9, 60($sp)
    sw $10, 56($sp)
    sw $11, 52($sp)
    sw $12, 48($sp)
    sw $13, 44($sp)
    sw $14, 40($sp)
    sw $15, 36($sp)
add_begin:
    # variable reference
    move $8, $16
    # variable reference
    move $9, $17
    # type coersion Int => Float
    # addition
    add $10, $8, $9
    # write
    li $v0, 1
    move $a0, $10
    syscall
add_end:
    # eiplogue
add_epilogue:
    # save floating point
    l.s $f4, 88($sp)
    l.s $f6, 84($sp)
    l.s $f8, 80($sp)
    l.s $f10, 76($sp)
    l.s $f16, 72($sp)
    l.s $f18, 68($sp)
    # load integers
    lw $8, 64($sp)
    lw $9, 60($sp)
    lw $10, 56($sp)
    lw $11, 52($sp)
    lw $12, 48($sp)
    lw $13, 44($sp)
    lw $14, 40($sp)
    lw $15, 36($sp)
    add $sp, $fp, 4
    lw $fp, 0($fp)
    jr $ra
.data
    add_framesize: .word 88
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
    s.s $f4, 88($sp)
    s.s $f6, 84($sp)
    s.s $f8, 80($sp)
    s.s $f10, 76($sp)
    s.s $f16, 72($sp)
    s.s $f18, 68($sp)
    # save integers
    sw $8, 64($sp)
    sw $9, 60($sp)
    sw $10, 56($sp)
    sw $11, 52($sp)
    sw $12, 48($sp)
    sw $13, 44($sp)
    sw $14, 40($sp)
    sw $15, 36($sp)
main_begin:
    # Int const
    li $11, 1
    # Int const
    li $12, 2
    # Int const
    li $13, 3
    # save parameters
    sw $23, 32($sp)
    sw $22, 28($sp)
    sw $21, 24($sp)
    sw $20, 20($sp)
    sw $19, 16($sp)
    sw $18, 12($sp)
    sw $17, 8($sp)
    sw $16, 4($sp)
    # moving parameters
    move $18, $13 
    move $17, $12 
    move $16, $11 
    # function call
    jal add_entry
    lw $23, 32($sp)
    lw $22, 28($sp)
    lw $21, 24($sp)
    lw $20, 20($sp)
    lw $19, 16($sp)
    lw $18, 12($sp)
    lw $17, 8($sp)
    lw $16, 4($sp)
    mov.s $f4, $f0
main_end:
    # eiplogue
main_epilogue:
    # save floating point
    l.s $f4, 88($sp)
    l.s $f6, 84($sp)
    l.s $f8, 80($sp)
    l.s $f10, 76($sp)
    l.s $f16, 72($sp)
    l.s $f18, 68($sp)
    # load integers
    lw $8, 64($sp)
    lw $9, 60($sp)
    lw $10, 56($sp)
    lw $11, 52($sp)
    lw $12, 48($sp)
    lw $13, 44($sp)
    lw $14, 40($sp)
    lw $15, 36($sp)
    add $sp, $fp, 4
    lw $fp, 0($fp)
    li $v0, 10
    syscall
.data
    main_framesize: .word 88
.data
