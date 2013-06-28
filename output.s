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
    s.s $f4, 56($sp)
    s.s $f6, 52($sp)
    s.s $f8, 48($sp)
    s.s $f10, 44($sp)
    s.s $f16, 40($sp)
    s.s $f18, 36($sp)
    sw $8, 32($sp)
    sw $9, 28($sp)
    sw $10, 24($sp)
    sw $11, 20($sp)
    sw $12, 16($sp)
    sw $13, 12($sp)
    sw $14, 8($sp)
    sw $15, 4($sp)
main_begin:
    # Int const
    li $8, 1
    # Int const initialization
    sw $8, -4($fp)
    # Float const
    li.s $f4, 2.300000
    # Int const initialization
    cvt.w.s $f4, $f4
    mfc1 $9, $f4
    sw $9, -8($fp)
    # Float const
    li.s $f6, 3.100000
    # Int const initialization
    cvt.w.s $f6, $f6
    mfc1 $10, $f6
    sw $10, -12($fp)
    # Int const
    li $11, 4
    # Int const initialization
    sw $11, -16($fp)
    # variable reference
    lw $12, -4($fp)
    # write
    li $v0, 1
    move $a0, $12
    syscall
    # variable reference
    lw $13, -8($fp)
    # write
    li $v0, 1
    move $a0, $13
    syscall
    # variable reference
    lw $14, -12($fp)
    # write
    li $v0, 1
    move $a0, $14
    syscall
    # variable reference
    lw $15, -16($fp)
    # write
    li $v0, 1
    move $a0, $15
    syscall
main_end:
    # eiplogue
main_epilogue:
    l.s $f4, 56($sp)
    l.s $f6, 52($sp)
    l.s $f8, 48($sp)
    l.s $f10, 44($sp)
    l.s $f16, 40($sp)
    l.s $f18, 36($sp)
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
    main_framesize: .word 72
.data
