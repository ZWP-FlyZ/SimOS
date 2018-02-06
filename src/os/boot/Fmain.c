/*
*
*   有header进入此次并在实模式进行初始配置
*
*
*/

#include "boot.h"
#include "ctypes.h"
#include "screen_info.h"
#include "bstring.h"
/*
*   进行更高级别的初始化，进入32位保护模式，
*   该函数不进行返回
*/



/*初始化键盘，并获取键盘状态*/
static void kbd_init()
{
    //获取键盘状态并赋值到
    char buf[10];
    boot_config_info.kbd_status= bios_kbd(0x0200);//获取键盘状态
    bios_kbd(0x0305); //设置键盘重复速率
    println("\n---> kbd_init finished!");
}

/* 设定64位模式*/
static void set_bios_mode(void)
{
#ifdef CONFIG_X86_64

#endif
}

/* 设置堆的起始位置 与 boot_static_info 中的heap_stack_end参数*/
char *HEAP;
char *heap_end;//堆尾，同栈尾
static void heap_init(void)
{
    RESET_HEAP();//重置堆头
    //剩余空间的中间位置当栈与堆的分界
    u32 hse= (((0xfffc + (u32)(&_end) )/2)&(-3));
    heap_end = (char *)hse;
    boot_static_info.heap_stack_end = (u16)hse;
    println("\n---> heap_init finished!");
}


void Fmain()
{
    u8 k = 20;
    u8 i = 0;

    println("FlyZ'OS is booting....\n");
    println("hello zwp\n");
    heap_init();

    //此处检查内存使用情况，
    //参考Linux boot/memory.c中，暂时不实现
    detect_memory();

    kbd_init();

    set_video();

    if(enable_a20())
        println("\n---> enable a20 ERROE!!!!");
    else
        println("\n---> enable a20 finished!!!!");

    k = sizeof(struct boot_static_info);
    print("k=");
    s8 str[10];
    number(str,k,10);    
    println(str);
    u8 *ori = (u8 *)(&boot_static_info);
    for(i=0;i<k;i++)
    {
        number(str,*(ori+i),16);
        print(str);
        print("  ");
    }

    number(str,boot_static_info.heap_stack_end,16);
    println(str);

    // 不返回 暂时使用
   while(1) {
       io_hlt();
       //_puts("hlt->");
   }
}

