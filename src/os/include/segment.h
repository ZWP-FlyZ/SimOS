#ifndef __SEGMENT_H_
#define __SEGMENT_H_
/*
* 提供包含模式下的一些定义与结构
*/

//定义GDT的项
#define GDT_BODY(base,limit,flag) \
		((((base) & 0xff000000ull)	<< 32) | \
		(((flag)  & 0x0000f0ffull)	<< 40) | \
		(((limit) & 0x000f0000ull)	<< 32) | \
		(((base)  & 0x00ffffffull)	<< 16) | \
		(((limit) & 0x0000ffffull)))         \


//boot时用的gdt项
#define GDT_BOOT_CS 2
#define BOOT_CS_OFF (GDT_BOOT_CS * 8)

#define GDT_BOOT_DS (GDT_BOOT_CS+1)
#define BOOT_DS_OFF (GDT_BOOT_CS * 8)





#endif



