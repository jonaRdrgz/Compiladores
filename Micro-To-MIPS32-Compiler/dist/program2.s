.text
.global main
main:
push {r4,lr}
ldr r0, addr_var1_scan
ldr r1, addr_var1_num
bl scanf
ldr  r1, Addvar1
ldr r1, [r1]
mov r1, r1
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
Addtr: .word tr

.data
return: .word 0
format: .asciz "%d\n"
var1: .word 0
var1_scan: .asciz "%d"
var1_num: .word 0
c: .word 2
d: .word 3
tr: .word 2

