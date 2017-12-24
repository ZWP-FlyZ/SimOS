/*
*   包含了一些中断汇编代码
*/

#include "bioscalls.h"

    .code16gcc
    .section .inittext

# 定义bios_putchar，在屏幕中打印一个字符
GLOBAL(bios_putchar)
    mov $0x77,%ax
ENDFUNC(bios_putchar)        







