.text
.global main
main:
push {r4,lr}

ldr r1, addr_var2
ldr r1, [r1]
ldr r2, addr_var2
ldr r2, [r2]
add r0, r1, r2
ldr r3, addr_var2
str r0, [r3]
ldr r5, addr_var2
ldr r5, [r5]
mov r1, r5
ldr r0, =format
bl printf


pop {r4,lr}
bx lr


address_of_return: .word return
addr_var2: .word var2
addr_var4: .word var4

.data
return: .word 0
format: .asciz "Se imprimio- %d\n"
var2: .word 2
var4: .word 3

