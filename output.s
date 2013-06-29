.data
    var_a:		.word 0
.text
g_entry:
    # prologue
    sw $ra, 0($sp)
    sw $fp, -4($sp)
    add $fp, $sp, -4
    add $sp, $sp, -8
    lw $2, g_framesize
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
g_begin:
    # variable reference
    lw $8, var_a
    # Int const
    li $9, 1
    # type coersion Int => Float
    # subtraction
    sub $10, $8, $9
    # assignment
    sw $10, var_a
    # variable reference
    lw $11, var_a
    # write
    li $v0, 1
    move $a0, $11
    syscall
g_end:
    # eiplogue
g_epilogue:
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
    g_framesize: .word 92
.data
.text
f_entry:
    # prologue
    sw $ra, 0($sp)
    sw $fp, -4($sp)
    add $fp, $sp, -4
    add $sp, $sp, -8
    lw $2, f_framesize
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
f_begin:
    # variable reference
    lw $12, var_a
    # Int const
    li $13, 1
    # type coersion Int => Float
    # subtraction
    sub $14, $12, $13
    # assignment
    sw $14, var_a
    # variable reference
    lw $15, var_a
    # write
    li $v0, 1
    move $a0, $15
    syscall
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
    # function call
    jal g_entry
    lw $23, 36($sp)
    lw $22, 32($sp)
    lw $21, 28($sp)
    lw $20, 24($sp)
    lw $19, 20($sp)
    lw $18, 16($sp)
    lw $17, 12($sp)
    lw $16, 8($sp)
    mov.s $f4, $f0
f_end:
    # eiplogue
f_epilogue:
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
    f_framesize: .word 92
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
    # Int const
    li $8, 5
    # assignment
    sw $8, var_a
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
    # function call
    jal f_entry
    lw $23, 36($sp)
    lw $22, 32($sp)
    lw $21, 28($sp)
    lw $20, 24($sp)
    lw $19, 20($sp)
    lw $18, 16($sp)
    lw $17, 12($sp)
    lw $16, 8($sp)
    mov.s $f6, $f0
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
