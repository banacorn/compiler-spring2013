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
    li $8, 5
    # Int const initialization
    sw $8, -8($fp)
    # Float const
    li.s $f4, 5.500000
    # Float const initialization
    s.s $f4, -16($fp)
    # variable reference
    lw $9, -8($fp)
    # write
    li $v0, 1
    move $a0, $9
    syscall
    # variable reference
    l.s $f6, -16($fp)
    # write
    li $v0, 2
    mov.s $f12, $f6
    syscall
    # Int const
    li $10, 0
    # return
    move $v0, $10
    j main_end
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
