/*
*
*
*
*
*/
#include "boot.h"


/*
*   进行更高级别的初始化，进入32位保护模式，
*   该函数不进行返回
*/
void Fmain()
{

    _putchar('A');
    _putchar('\n');
    _puts("hello world\n");
    _puts("hello zwp\t");
    while(1);// 不返回 暂时使用
}

