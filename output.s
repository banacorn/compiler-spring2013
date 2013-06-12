.data
.text
main:
    sw $ra, 0($sp)
    sw $fp, -4($sp)
    add $fp, $sp, -4
    add $sp, $sp, -8
    lw $2, main_framesize
    sub $sp, $sp, $2
    sw $8, 32($sp)
    sw $9, 28($sp)
    sw $10, 24($sp)
    sw $11, 20($sp)
    sw $12, 16($sp)
    sw $13, 12($sp)
    sw $14, 8($sp)
    sw $15, 4($sp)
main_begin:
    li.s $f4, 1.000000
    li $8, 1
    mtc1 $8, $f6
    cvt.s.w $f6, $f6
    c.eq.s $f4, $f6
    bc1t label_0
    li $9, 0
    j label_exit_0
label_0:
    li $9, 1
label_exit_0:
    sw $9, -4($fp)
    lw $10, -4($fp)
    li $v0, 1
    move $a0, $10
    syscall
    li $11, 0
    move $v0, $11
    j main_end
main_end:
main_epilogue:
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
    main_framesize: .word 36
.data
