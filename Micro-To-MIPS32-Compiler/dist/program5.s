.text
.global main
main:
push {r4,lr}
mov r1, #5
ldr r2, addr_var1
ldr r2, [r2]
sub r0, r1, r2
ldr r3, addr_var1
str r0, [r3]
ldr r0, addr_var2_scan
ldr r1, addr_var2_num
bl scanf
ldr r0, addr_var2_num
ldr r0,[r0]
ldr r1,addr_var2
str r0,[r1]
ldr r5, addr_var2
ldr r5, [r5]
mov r6, #10
add r4, r5, r6
ldr r7, addr_var3
str r4, [r7]
mov r8, #0
ldr r9, addr_var3
ldr r9, [r9]
cmp r9, r8
bne label0
ldr r1, addr_var1
ldr r1, [r1]
mov r2, #5
add r0, r1, r2
ldr r3, addr_var3
str r0, [r3]
mov r4, #0
ldr r5, addr_var3
ldr r5, [r5]
cmp r5, r4
bne label2
mov r7, #4
ldre  r8, addr_var3
str r7, [r8]
b label3
label2:
mov r0, #5
ldre  r1, addr_var3
str r0, [r1]
label3:
ldr  r2, addr_var3
ldr r2, [r2]
b label1
label0:
mov  r2, #10
label1:
ldr r3, addr_var3
str r2, [r3]
ldr  r5, addr_var3
ldr r5, [r5]
mov r1, r5
ldr r0, =format
bl printf
pop {r4,lr}
bx lr


address_of_return: .word return
addr_var1: .word var1
addr_var2: .word var2
addr_var2_scan: .word var2_scan
addr_var2_num: .word var2_num
addr_var3: .word var3

.data
return: .word 0
format: .asciz "Se imprimio- %d\n"
var1: .word 15
var2: .word 0
var2_scan: .asciz "%d"
var2_num: .word 0
var3: .word 0

