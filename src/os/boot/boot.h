

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


// 位于header部分的 两个启动信息
extern struct boot_static_info boot_static_info;
extern struct boot_config_info boot_config_info;

extern char _end[]; //boot结尾处，在boot.ld中定义
extern char * HEAP ;//堆头指针
extern char *heap_end;//堆尾，同栈尾

#define RESET_HEAP() ((void *)(HEAP = _end))

//
void io_hlt();
void io_cli();
void io_sti();
void die();
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


// video 设置 video.c
void set_video();


// // 保护模式跳转
// void go_to_protect_model();

#endif

