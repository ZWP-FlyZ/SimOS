#ifndef __BIOSCALLS_H_
#define __BIOSCALLS_H_

#ifdef __ASSEMBLY__
// 定义操作开头
#define GLOBAL(name)    \
        .global name;   \
        name:

// 定义函数尾
#define ENDFUNC(name)   \
        .type name, @function   \
        .size name, .-name
#endif //endif __ASSEMBLY__

void bios_putchar(int c);

#endif