/*
*实现实模式下putchar puts的功能
*
*/

#include "boot.h"

/*putchar代码参考linux boot/tty.c */
void __attribute__((section(".inittext")))_putchar(int c)
{
    if(c == '\n')
        _putchar('\r');//输出 \r\n进行换行回头
    bios_putchar(c);
}

void __attribute__((section(".inittext")))_puts(const char *str)
{
    while(*str)
        _putchar(*str++);
}

void __attribute__((section(".inittext")))printc(int c)
{
       _putchar(c); 
} 

void __attribute__((section(".inittext")))print(const char *str)
{
       while(*str) _putchar(*str++); 
} 

void __attribute__((section(".inittext")))println(const char *str)
{
       while(*str) _putchar(*str++); 
        _putchar('\n');
} 






