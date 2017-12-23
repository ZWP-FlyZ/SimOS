

#ifndef __BOOT_H_
#define __BOOT_H_


//header.S 代码被导入内存中的段值
#define HEADER_IN_SEQ_ADDR 0x0800

//header.S 代码被导入内存中的线性地址
#define HEADER_IN_LINE_ADDR 0x8000 

// header.S 预留空间大小
#define EMPTY_AREA 512

//内核启动代码区和堆栈区大小，两者之和小于64k
#define BOOTSETUP_CODE_AREA_SIZE 0x8000
#define BOOTSETUP_HEAP_AREA_SIZE 0x8000

// void puts(const char *);
// void putchar(int);

#endif

