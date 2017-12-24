/*
*实现实模式下putchar puts的功能
*
*/


#include "boot.h"
#include "bioscalls.h"

/*putchar代码参考linux boot/tty.c */
void __attribute__((section(".inittext")))putchar(int c)
{
    if(c == '\n')
        putchar('\r');//输出 \r\n进行换行回头
    bios_putchar(c);
}

void __attribute__((section(".inittext")))puts(const char *str)
{
    
}






