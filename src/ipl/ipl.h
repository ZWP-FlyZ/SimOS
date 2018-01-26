#ifndef __IPL_H_
#define __IPL_H_

// boot起始段地址
#define BOOTSEQ  0x07c0

// header.S 代码被导入内存中的段值与偏移量
#define HEADER_IN_SEQ_ADDR   0x0800
#define HEADER_IN_OFF_ADDR   0x0

// entry偏移地址
#define START_ENTRY_OFFSET  0x20
#define START_ENTRY_IN_SEQ_ADDR  (HEADER_IN_SEQ_ADDR + START_ENTRY_OFFSET)


// 读取柱面数,
#define CYLS  10

// 错误读取计数
#define ERR_READ_COUT  5


#endif