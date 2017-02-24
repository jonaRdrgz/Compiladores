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
ldr  r4, addr_var2
ldr r4, [r4]
mov r5, #0
cmp r4, r5
bne label0
ldr  r6, addr_var1
ldr r6, [r6]
mov r7, #0
cmp r6, r7
bne label2
mov  r6, #4
b label3
label2:
mov  r6, #5
label3:
mov r4, r6
b label1
label0:
mov  r4, #10
label1:
ldr r8, addr_var3
str r4, [r8]
ldr  r0, addr_var3
ldr r0, [r0]
mov r1, r0
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
var1: .word 2
var2: .word 0
var2_scan: .asciz "%d"
var2_num: .word 0
var3: .word 0

