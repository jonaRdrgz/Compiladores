.text
.global main
main:
push {r4,lr}
ldr r1, Addvar2
ldr r1, [r1]
ldr r2, Addvar2
ldr r2, [r2]
add r0, r1, r2
mov r4, r0
mov r5, #4
add r3, r4, r5
mov r7, r3
mov r8, #6
add r6, r7, r8
ldr r0, Addvar2
str r6, [r0]
ldr r2, Addvar2
ldr r2, [r2]
ldr r3, Addvar4
ldr r3, [r3]
add r1, r2, r3
ldr r5, Addvar2
str r1, [r5]
ldr  r7, Addvar2
ldr r7, [r7]
mov r1, r7
ldr r0, =format
bl printf
pop {r4,lr}
bx, lr


address_of_return: return
Addvar2: .word var2
Addvar4: .word var4

.data
return: .word 0
format: .asciz "%d\n"
var2: .word 2
var4: .word 3
ñ¸
