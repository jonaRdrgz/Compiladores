.text
.globl main
main:
li $v0, 1
li $a0, 10
syscall
li $a0, 10
li $v0, 11
syscall
li $t1, 4
li $t3, 6
move $t4, $t1
sub $t2, $t3, $t4
move $t6, $t2
li $t7, 1
sub $t5, $t6, $t7
li $v0, 1
li $a0, 1
syscall
li $a0, 10
li $v0, 11
syscall
li $v0, 10
syscall

.data

