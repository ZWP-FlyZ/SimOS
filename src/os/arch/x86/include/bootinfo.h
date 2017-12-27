#ifndef __BOOTINFO_H_
#define __BOOTINFO_H_

/*
*   保存boot信息，保存在header.s 中那预留位上
*/

#include "ctype.h"
#include "screen_info.h"

struct boot_info 
{

    u8  kbd_status;//键盘状态
    u32 code32_start;    //保护模式起始地址
    struct screen_info screen_info;
}__attribute__((packed));




#endif 