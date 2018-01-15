
#include "boot.h"
#include "ctypes.h"
#include "segment.h"

/*
*   以下代码参考linux，linux boot/pm.c
*   
*
*/


//关闭所有中断
static void close_interrupt()
{
    asm volatile("cli");//不普通中断
    outb(0x70,0x80); //使用0x70端口关闭NMI中断
    io_delay();
}

//重置协处理器
static void reset_coprocess()
{
    outb(0xf0,0);
	io_delay();
	outb(0xf1,0);
	io_delay();
}

//在这里处理PIC芯片，将所有外部中断的端口屏蔽
static void mask_pic()
{
    outb(0x21,0xff);//屏蔽主PIC芯片
	io_delay();
	outb(0xf1,0);//屏蔽从PIC芯片
	io_delay();
}


//定义一个gdtr内容的结构
//总共48个字节
struct gdtr{
	u16 len;
	u32 addr;
} __attribute__((packed));

//设置boot时的GDT表
static void set_gdt()
{
	//这里使用 16字节对齐，这需要同gdtr.len 配合去除多余的u64
	static const u64 boot_gdt[] __attribute__((aligned(16)))= {
		//boot代码段，可执行可读可访问flag = 1100 0000 1001 1011 
		[GDT_BOOT_CS] = GDT_BODY(0x0,0xffffffff,0xc09b) ,
		//boot数据段 可读可写可访问flag = 1100 0000 1001 0011 
		[GDT_BOOT_DS] = GDT_BODY(0x0,0xffffffff,0xc093)
	};

	static struct gdtr gdt;
	gdt.len = sizeof(boot_gdt);
	gdt.addr = (u32)&gdt + (ds()<<4);

	asm volatile("lgdtl %0" : : "m" (gdt));

}

//设置中断向量
void set_idt(){
	static struct gdtr idt = {0,0}; //这里设置的idtr内容与gdtr一样
	//在这一阶段，设置一个空的idtr,在之后会进行正式设置
	asm volatile("lidtl %0" : : "m" (idt));
}


void go_to_protect_model()
{
	close_interrupt();
	reset_coprocess();
	mask_pic();
	set_gdt();
	set_idt();
	protect_model_jump();
}












