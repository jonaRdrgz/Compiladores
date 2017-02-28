.text
.global main
main:
push {r4,lr}
mov r1, #2
ldr r0, =format
bl printf
pop {r4,lr}
bx lr


address_of_return: .word return

.data
return: .word 0
format: .asciz "Se imprimio- %d\n"

