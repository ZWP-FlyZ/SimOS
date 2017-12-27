

#ifndef _BOOT_H_
#define _BOOT_H_

//header.S 代码被导入内存中的段值
#define HEADER_IN_SEQ_ADDR 0x0800
//header.S 代码被导入内存中的线性地址
#define HEADER_IN_LINE_ADDR 0x8000 

//内核启动代码区和堆栈区大小，两者之和小于64k
#define BOOTSETUP_CODE_AREA_SIZE 0x8000
#define BOOTSETUP_HEAP_AREA_SIZE 0x8000

#define BOOT_PARAMS_ADDR 




/*启动配置阶段定义的类型符合*/

void io_hlt();
void io_cli();
void io_sti();
void die();

// 


/* 16位模式下字符信息输出 tty.c*/
void bios_putchar(int c);
void _puts(const char *);
void _putchar(int);


// video 设置 video.c
void set_video();

// // 保护模式跳转
// void go_to_protect_model();

#endif

