.text
.global main
main:
push {r4,lr}
ldr r1, addr_var1
ldr r1, [r1]
mov r2, #2
add r0, r1, r2
ldr r3, addr_var2
str r0, [r3]
ldr  r5, addr_var2
ldr r5, [r5]
mov r1, r5
ldr r0, =format
bl printf
pop {r4,lr}
bx lr


address_of_return: .word return
addr_var1: .word var1
addr_var2: .word var2

.data
return: .word 0
format: .asciz "Se imprimio- %d\n"
var1: .word 1
var2: .word 0

