/*
*   包含了一些中断汇编代码
*/


    .code16gcc
    .section .inittext

# 定义bios_putchar，在屏幕中打印一个字符
# 函数原型 void bios_putchar(int)
    .global bios_putchar 
bios_putchar: 
    pushl %ebp
    movl  %esp,%ebp
    pushl %eax
    pushl %ebx

    movb 8(%ebp),%al
    mov $0x0e,%ah
    mov $15,%bx
    int $0x10

    popl %ebx
    popl %eax
    nop
    leavel  # bp sp opration
    retl
# bios_putchar 结束




 




