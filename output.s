.data
    a:		.word -4
    bb:		.word 4
    c:		.word -4
    d:		.word 4
    e:		.float -1.000000
    f:		.float 1.000000
    g:		.float -1.500000
    h:		.float 1.500000
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
    # variable reference
    lw $8, a
    # write
    li $v0, 1
    move $a0, $8
    syscall
    # variable reference
    lw $9, bb
    # write
    li $v0, 1
    move $a0, $9
    syscall
    # variable reference
    lw $10, c
    # write
    li $v0, 1
    move $a0, $10
    syscall
    # variable reference
    lw $11, d
    # write
    li $v0, 1
    move $a0, $11
    syscall
    # variable reference
    l.s $f4, e
    # write
    li $v0, 2
    mov.s $f12, $f4
    syscall
    # variable reference
    l.s $f6, f
    # write
    li $v0, 2
    mov.s $f12, $f6
    syscall
    # variable reference
    l.s $f8, g
    # write
    li $v0, 2
    mov.s $f12, $f8
    syscall
    # variable reference
    l.s $f10, h
    # write
    li $v0, 2
    mov.s $f12, $f10
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
    main_framesize: .word 56
.data
