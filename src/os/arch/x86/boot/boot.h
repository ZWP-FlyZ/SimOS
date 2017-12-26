

#ifndef _BOOT_H_
#define _BOOT_H_

//#include <stdint.h>

//header.S 代码被导入内存中的段值
#define HEADER_IN_SEQ_ADDR 0x0800

//header.S 代码被导入内存中的线性地址
#define HEADER_IN_LINE_ADDR 0x8000 
// header.S 预留空间大小
#define EMPTY_AREA 512
//内核启动代码区和堆栈区大小，两者之和小于64k
#define BOOTSETUP_CODE_AREA_SIZE 0x8000
#define BOOTSETUP_HEAP_AREA_SIZE 0x8000

// /*启动配置阶段定义的类型符合*/
// typedef int8_t  s8;
// typedef int16_t s16;
// typedef int32_t s32;
// typedef int64_t s64;
// typedef uint8_t  u8;
// typedef uint16_t u16;
// typedef uint32_t u32;
// typedef uint64_t u64;

// /* 定义当前寄存器 sizeof 11*u32 */
// typedef struct Bios_Regs {
//     union{
//         //32位寄存器
//         struct reg32{
//             u32 eax;
//             u32 ecx;
//             u32 edx;
//             u32 ebx;
//             u32 esp;
//             u32 ebp;
//             u32 edi;
//             u32 esi;
//             u32 _fsgs;
//             u32 _esds;
//             u32 eflag            
//         };
//         //16位寄存器,h*表示高16位
//         struct reg16{
//             u16 ax,hax;
//             u16 cx,hcx;
//             u16 dx,hdx;
//             u16 bx,hbx;
//             u16 sp,hsp;
//             u16 bp,hbp;
//             u16 di,hdi;
//             u16 si,hsi;
//             u16 fs,gs;
//             u16 es,ds;
//             u16 flag,hflag;                        
//         } ;
//         //8位寄存器
//         struct reg8{
//             u8 al,ah,eax2,eax3;
//             u8 cl,ch,ecx2,ecx3;
//             u8 dl,dh,edx2,edx3;
//             u8 bl,bh,ebx2,ebx3;
//             u8 spl,sph,esp2,esp3;
//             u8 bpl,bph,ebp2,ebp3;
//             u8 dil,dih,edi2,edi3;
//             u8 sil,sih,esi2,esi3;
//         };
//     };
// } bios_regs;

void io_hlt();
void die();

/* 16位模式下字符信息输出 tty.c*/
void bios_putchar(int c);
void _puts(const char *);
void _putchar(int);

#endif

