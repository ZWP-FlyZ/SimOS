/*
*
*
*
*
*/
#include "boot.h"
#include "ctypes.h"
#include "screen_info.h"
/*
*   进行更高级别的初始化，进入32位保护模式，
*   该函数不进行返回
*/
void Fmain()
{
    u8 k = 20;
    u8 i = 0;
    u8 *start1 = (u8 *)0xb8000;
    u8 *start2 = (u8 *)0xb0000;    
    _putchar('A');
    _putchar('\n');
    _puts("hello world\n");
    _puts("hello zwp\n");
    struct screen_info screen_info;
    screen_info.vmode = (u16)('K');
    _putchar(screen_info.vmode);
    initScrInfo(&screen_info);
    _putchar(screen_info.vmode);

    for(i=0;i<k;i++)
    {
        _putchar(start1[i]);
    }
    _putchar('\n');
    for(i=0;i<k;i++)
    {
        _putchar(start2[i]);
    }
    // 不返回 暂时使用
   while(1) {
       io_hlt();
       //_puts("hlt->");
   }
}

