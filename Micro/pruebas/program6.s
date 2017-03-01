.text
.global main
main:
push {r4,lr}
ldr r0, addr_var1_scan
ldr r1, addr_var1_num
bl scanf
ldr r0, addr_var1_num
ldr r0,[r0]
ldr r1,addr_var1
str r0,[r1]
ldr  r0, addr_var1
ldr r0, [r0]
mov r1, #0
cmp r0, r1
bne label0
mov  r0, #0
b label1
label0:
mov  r0, #1
label1:
ldr r2, addr_var2
str r0, [r2]
mov r3, #0
ldr r4, addr_var2
ldr r4, [r4]
cmp r4, r3
bne label2
mov r6, #123
ldr  r7, addr_var2
str r6, [r7]
b label3
label2:
mov r9, #3
ldr  r0, addr_var2
str r9, [r0]
label3:
ldr r2, addr_var2
ldr r2, [r2]
mov r3, #600
add r1, r2, r3
mov r5, r1
mov r6, #60
add r4, r5, r6
mov r8, r4
mov r9, #6
add r7, r8, r9
ldr r0, addr_var2
str r7, [r0]
ldr  r2, addr_var1
ldr r2, [r2]
mov r1, r2
ldr r0, =format
bl printf
ldr  r4, addr_var2
ldr r4, [r4]
mov r1, r4
ldr r0, =format
bl printf
pop {r4,lr}
bx lr


address_of_return: .word return
addr_var1: .word var1
addr_var1_scan: .word var1_scan
addr_var1_num: .word var1_num
addr_var2: .word var2

.data
return: .word 0
format: .asciz "Se imprimio- %d\n"
var1: .word 0
var1_scan: .asciz "%d"
var1_num: .word 0
var2: .word 0

