#ifndef __STRUCTS_H_
#define __STRUCTS_H_

#include "ctypes.h"

/* 定义当前寄存器 sizeof 11*u32 */
struct bios_regs {
    union{
        struct reg32{
            u32 eax;
            u32 ecx;
            u32 edx;
            u32 ebx;
            u32 esp;
            u32 ebp;
            u32 edi;
            u32 esi;
            u32 _fsgs;
            u32 _esds;
            u32 eflag            
        };
        struct reg16{
            u16 ax,hax;
            u16 cx,hcx;
            u16 dx,hdx;
            u16 bx,hbx;
            u16 sp,hsp;
            u16 bp,hbp;
            u16 di,hdi;
            u16 si,hsi;
            u16 fs,gs;
            u16 es,ds;
            u16 flag,hflag;                        
        };
        struct reg8{
            u8 al,ah,eax2,eax3;
            u8 cl,ch,ecx2,ecx3;
            u8 dl,dh,edx2,edx3;
            u8 bl,bh,ebx2,ebx3;
            u8 spl,sph,esp2,esp3;
            u8 bpl,bph,ebp2,ebp3;
            u8 dil,dih,edi2,edi3;
            u8 sil,sih,esi2,esi3;
        };
    };
};

/* 定义 系统配置信息 */




#endif