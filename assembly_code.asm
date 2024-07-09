.data:
n:.byte 3 4 5
m:.word 4 5 6
l:.asciiz "ASRA"
.text:
lui x20, 10
add x1, x2, x3
lw x10,0(x20)
jal x1,fact
jal x0,full_exit
fact:
sw  x1,4(x1)
sw  x10, 0(x1)
addi x5,x10,-8
addi x7, x0, 1
bge  x5, x7, L1
blt x6,x8,fact
addi x10,x0,1
addi x2,x2,8
jalr x0,x1,0
L1:
addi x10,x10,-1
jal  x1,fact
addi x6,x10,0
lw  x10,0(x6)
lw  x1,-4(x5)
sw x2,-21(x6)
addi x6,x6,8
#hello
mul x10,x10,x6
jalr x0,x1,0
full_exit:
# All good, check the stack pointer and register x10
