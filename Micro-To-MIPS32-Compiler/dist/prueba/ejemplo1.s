.text
.global main
main:
push {r4,lr}
mov r1, #2
ldr r0, =format
bl printf
ldr r2, addr_var1
ldr r2, [r2]
mov r3, #2
add r1, r2, r3
ldr r4, addr_var2
str r1, [r4]
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

