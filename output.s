.data
.text
lesen_entry:
    # prologue
    sw $ra, 0($sp)
    sw $fp, -4($sp)
    add $fp, $sp, -4
    add $sp, $sp, -8
    lw $2, lesen_framesize
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
lesen_begin:
    # read
    li $v0, 6
    syscall
    mov.s $f4, $f0
    # return
    mov.s $f0, $f4
    j lesen_end
lesen_end:
    # eiplogue
lesen_epilogue:
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
    jr $ra
.data
    lesen_framesize: .word 56
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
f_begin:
    # function call
    jal lesen_entry
    mov.s $f6, $f0
    cvt.w.s $f6, $f6
    mfc1 $8, $f6
    # return
    move $v0, $8
    j f_end
f_end:
    # eiplogue
f_epilogue:
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
    jr $ra
.data
    f_framesize: .word 56
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
    # function call
    jal f_entry
    move $9, $v0
    # write
    li $v0, 1
    move $a0, $9
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
