#ifndef __CREEN_INFO_H_
#define __CREEN_INFO_H_

#include "ctypes.h"

//默认 80*25 16色 文本模式
#define VMODE_TEXT_03H 0x1 
#define SCR_X_SIZE_03H 80 
#define SCR_Y_SIZE_03H 25 
#define VRAM_ADDR_03H 0xB8000
#define REG_AX_SET_03H 0x0003 

// 640*480 256色 视频模式
#define VMODE_GRAPH_13H 0x2 
#define SCR_X_SIZE_13H 640 
#define SCR_Y_SIZE_13H 480 
#define VRAM_ADDR_13H 0xA0000
#define REG_AX_SET_13H 0x0013 

// size 80Byte
struct screen_info 
{
    u16 vmode;
    u16 screen_x ;
    u16 screen_y ;
    u32 vram;
} __attribute__((packed));


static inline void initScrInfo(struct screen_info *info)
{
    info->vmode = 0;
    info->screen_x = 0;
    info->screen_y = 0;
    info->vram = 0;    
}


#endif