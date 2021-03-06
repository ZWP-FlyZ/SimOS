

#ifndef _BOOT_H_
#define _BOOT_H_

#include "bootinfo.h"

//header.S 代码被导入内存中的段值
#define HEADER_IN_SEQ_ADDR 0x0800
//header.S 代码被导入内存中的线性地址
#define HEADER_IN_LINE_ADDR 0x8000 

//内核启动代码区和堆栈区大小，两者之和小于64k
#define BOOTSETUP_CODE_AREA_SIZE 0x8000
#define BOOTSETUP_HEAP_AREA_SIZE 0x8000


#define cpu_relax()	asm volatile("rep; nop")
//参考自linux boot.h,io

static inline  void io_hlt(){
    __asm__ ("hlt"); 
}
static inline void io_cli(){
    __asm__ ("cli"); 
}
static inline void io_sti(){
    __asm__ ("sti"); 
}
static inline void outb(u16 port,u8 v)
{
	asm volatile("outb %0,%1" : : "a" (v), "dN" (port));
}
static inline u8 inb(u16 port)
{
	u8 v;
	asm volatile("inb %1,%0" : "=a" (v) : "dN" (port));
	return v;
}

static inline void outw(u16 port,u16 v)
{
	asm volatile("outw %0,%1" : : "a" (v), "dN" (port));
}
static inline u16 inw(u16 port)
{
	u16 v;
	asm volatile("inw %1,%0" : "=a" (v) : "dN" (port));
	return v;
}

static inline void outl(u16 port,u32 v )
{
	asm volatile("outl %0,%1" : : "a" (v), "dN" (port));
}
static inline u32 inl(u16 port)
{
	u32 v;
	asm volatile("inl %1,%0" : "=a" (v) : "dN" (port));
	return v;
}

static inline void io_delay(void)
{
	const u16 DELAY_PORT = 0x80;
	asm volatile("outb %%al,%0" : : "dN" (DELAY_PORT));
}

static inline u16 ds(void)
{
	u16 seg;
	asm("movw %%ds,%0" : "=rm" (seg));
	return seg;
}

static inline void set_fs(u16 seg)
{
	asm volatile("movw %0,%%fs" : : "rm" (seg));
}
static inline u16 fs(void)
{
	u16 seg;
	asm volatile("movw %%fs,%0" : "=rm" (seg));
	return seg;
}

static inline void set_gs(u16 seg)
{
	asm volatile("movw %0,%%gs" : : "rm" (seg));
}
static inline u16 gs(void)
{
	u16 seg;
	asm volatile("movw %%gs,%0" : "=rm" (seg));
	return seg;
}

typedef unsigned int addr_t;

static inline u8 rdfs8(addr_t addr)
{
	u8 v;
	asm volatile("movb %%fs:%1,%0" : "=q" (v) : "m" (*(u8 *)addr));
	return v;
}
static inline u16 rdfs16(addr_t addr)
{
	u16 v;
	asm volatile("movw %%fs:%1,%0" : "=r" (v) : "m" (*(u16 *)addr));
	return v;
}
static inline u32 rdfs32(addr_t addr)
{
	u32 v;
	asm volatile("movl %%fs:%1,%0" : "=r" (v) : "m" (*(u32 *)addr));
	return v;
}

static inline void wrfs8(u8 v, addr_t addr)
{
	asm volatile("movb %1,%%fs:%0" : "+m" (*(u8 *)addr) : "qi" (v));
}
static inline void wrfs16(u16 v, addr_t addr)
{
	asm volatile("movw %1,%%fs:%0" : "+m" (*(u16 *)addr) : "ri" (v));
}
static inline void wrfs32(u32 v, addr_t addr)
{
	asm volatile("movl %1,%%fs:%0" : "+m" (*(u32 *)addr) : "ri" (v));
}

static inline u8 rdgs8(addr_t addr)
{
	u8 v;
	asm volatile("movb %%gs:%1,%0" : "=q" (v) : "m" (*(u8 *)addr));
	return v;
}
static inline u16 rdgs16(addr_t addr)
{
	u16 v;
	asm volatile("movw %%gs:%1,%0" : "=r" (v) : "m" (*(u16 *)addr));
	return v;
}
static inline u32 rdgs32(addr_t addr)
{
	u32 v;
	asm volatile("movl %%gs:%1,%0" : "=r" (v) : "m" (*(u32 *)addr));
	return v;
}

static inline void wrgs8(u8 v, addr_t addr)
{
	asm volatile("movb %1,%%gs:%0" : "+m" (*(u8 *)addr) : "qi" (v));
}
static inline void wrgs16(u16 v, addr_t addr)
{
	asm volatile("movw %1,%%gs:%0" : "+m" (*(u16 *)addr) : "ri" (v));
}
static inline void wrgs32(u32 v, addr_t addr)
{
	asm volatile("movl %1,%%gs:%0" : "+m" (*(u32 *)addr) : "ri" (v));
}


// 位于header部分的 两个启动信息
extern struct boot_static_info boot_static_info;
extern struct boot_config_info boot_config_info;

extern char _end[]; //boot结尾处，在boot.ld中定义
extern char * HEAP ;//堆头指针
extern char *heap_end;//堆尾，同栈尾

#define RESET_HEAP() ((void *)(HEAP = _end))

//
// void __attribute__((fastcall))io_hlt() ;
// void __attribute__((fastcall))io_cli();
// void __attribute__((fastcall))io_sti();
void __attribute__((fastcall))die();
void __attribute__((fastcall))error_die();
void __stack_chk_fail();


//bioscalls.s bios中断，可以使用fastcall，
//但这还是栈参数调用
void bios_putchar(int c);
unsigned char bios_kbd(unsigned short); //键盘中断

/* 16位模式下字符信息输出 tty.c*/
void _puts(const char *);
void _putchar(int);
void printc(int);
void print(const char *);
void println(const char *);


//memory.c
void detect_memory();

// video 设置 video.c
void set_video();




// 开启A20寻址 a20.c
int __attribute__((fastcall))enable_a20();


// // 保护模式初始化与跳转
// protectmode.c pm_jump.S
void __attribute__((noreturn))go_to_protect_model();
void __attribute__((noreturn,fastcall))protect_model_jump(u32 code32_start,u32 param_addr);
#endif

