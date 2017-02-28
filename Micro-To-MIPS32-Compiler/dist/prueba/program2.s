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
ldr r1, addr_var1
ldr r1, [r1]
mov r2, #1
sub r0, r1, r2
ldr r3, addr_c
str r0, [r3]
ldr r5, addr_c
ldr r5, [r5]
mov r1, r5
ldr r0, =format
bl printf


pop {r4,lr}
bx lr


address_of_return: .word return
addr_var1: .word var1
addr_var1_scan: .word var1_scan
addr_var1_num: .word var1_num
addr_c: .word c
addr_a: .word a

.data
return: .word 0
format: .asciz "Se imprimio- %d\n"
var1: .word 0
var1_scan: .asciz "%d"
var1_num: .word 0
c: .word 0
a: .word 2

