/*
*
*   有header进入此次并在实模式进行初始配置
*
*
*/
#include "boot.h"
#include "ctypes.h"
#include "screen_info.h"
#include "bstring.h"
/*
*   进行更高级别的初始化，进入32位保护模式，
*   该函数不进行返回
*/
void Fmain()
{
    u8 k = 20;
    u8 i = 0;
    u8 *start1 = (u8 *)0x2d4;
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

    _putchar('\n');

    k = sizeof(struct boot_static_info);
    s8 str[10];
    s8 *ori = (char *)(&boot_static_info);
    for(i=0;i<k;i++)
    {
        number(str,*(ori+i),16);
        _puts(str);
        _puts(" \n"); 
    }
    _puts(boot_static_info.strinfo);


    set_video();

    // 不返回 暂时使用
   while(1) {
       io_hlt();
       //_puts("hlt->");
   }
}

