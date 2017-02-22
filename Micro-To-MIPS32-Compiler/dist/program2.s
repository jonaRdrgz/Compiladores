.text
.global main
main:
push {r4,lr}
ldr r0, addr_var1_scan
ldr r1, addr_var1_num
bl scanf
mov r1, #3
ldr r2, Addc
ldr r2, [r2]
add r0, r1, r2
ldr r4, Addd
str r0, [r4]
ldr r6, Addd
ldr r6, [r6]
mov r7, #1
add r5, r6, r7
ldr r9, Addc
str r5, [r9]
ldr  r1, Addvar1
ldr r1, [r1]
mov r1, r1
ldr r0, =format
bl printf
ldr  r3, Addd
ldr r3, [r3]
mov r1, r3
ldr r0, =format
bl printf
ldr  r5, Addc
ldr r5, [r5]
mov r1, r5
ldr r0, =format
bl printf
pop {r4,lr}
bx, lr


address_of_return: return
Addvar1: .word var1
addr_var1_scan: .word var1_scan
addr_var1_num: .word var1_num
Addc: .word c
Addd: .word d

.data
return: .word 0
format: .asciz "Se imprimio- %d\n"
var1: .word 0
var1_scan: .asciz "%d"
var1_num: .word 0
c: .word 2
d: .word 0

