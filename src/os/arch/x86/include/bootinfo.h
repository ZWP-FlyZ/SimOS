#ifndef __BOOTINFO_H_
#define __BOOTINFO_H_

/*
*   保存boot信息，保存在header.s 中那预留位上
*/

#include "ctypes.h"
#include "screen_info.h"

//静态boot信息
struct boot_static_info
{
    s8  strinfo[8];    //长度为16的文字信息
    u32 code16_start;
    u32 code32_start;    //保护模式起始地址
}__attribute__((packed));

//可更替信息的信息
struct boot_config_info 
{
    u8  kbd_status;//键盘状态
    struct screen_info screen_info;
}__attribute__((packed));



#endif 