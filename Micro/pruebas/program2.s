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
mov r1, #3
ldr r2, addr_c
ldr r2, [r2]
add r0, r1, r2
ldr r3, addr_d
str r0, [r3]
ldr r5, addr_d
ldr r5, [r5]
mov r6, #1
add r4, r5, r6
ldr r7, addr_c
str r4, [r7]
pop {r4,lr}
bx lr


address_of_return: .word return
addr_var1: .word var1
addr_var1_scan: .word var1_scan
addr_var1_num: .word var1_num
addr_c: .word c
addr_d: .word d

.data
return: .word 0
format: .asciz "Se imprimio- %d\n"
var1: .word 0
var1_scan: .asciz "%d"
var1_num: .word 0
c: .word 2
d: .word 0

