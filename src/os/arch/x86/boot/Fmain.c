/*
*
*
*
*
*/
#include "boot.h"
#include "ctypes.h"
#include "regs.h"
/*
*   进行更高级别的初始化，进入32位保护模式，
*   该函数不进行返回
*/
void Fmain()
{
    u8 k = 10;
    struct bios_regs regs;
    _putchar('A');
    _putchar('\n');
    _puts("hello world\n");
    _puts("hello zwp");


    // 不返回 暂时使用
   while(1) {
       io_hlt();
       _puts("hlt->");
   }
}

