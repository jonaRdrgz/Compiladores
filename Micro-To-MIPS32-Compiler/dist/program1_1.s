.text
.global main
main:
push {r4,lr}
ldr r1, addr_var2
ldr r1, [r1]
ldr r2, addr_var2
ldr r2, [r2]
add r0, r1, r2
mov r4, r0
mov r5, #4
add r3, r4, r5
mov r7, r3
mov r8, #6
add r6, r7, r8
ldr r9, addr_var2
str r6, [r9]
ldr r1, addr_var2
ldr r1, [r1]
ldr r2, addr_var4
ldr r2, [r2]
add r0, r1, r2
ldr r3, addr_var2
str r0, [r3]
ldr r5, addr_var4
ldr r5, [r5]
ldr r6, addr_var2
ldr r6, [r6]
add r4, r5, r6
ldr r7, addr_var5
str r4, [r7]
ldr r9, addr_var2
ldr r9, [r9]
ldr r0, addr_var5
ldr r0, [r0]
add r8, r9, r0
ldr r1, addr_var6
str r8, [r1]
pop {r4,lr}
bx lr


address_of_return: .word return
addr_var2: .word var2
addr_var4: .word var4
addr_var5: .word var5
addr_var6: .word var6

.data
return: .word 0
format: .asciz "Se imprimio- %d\n"
var2: .word 2
var4: .word 3
var5: .word 0
var6: .word 0

