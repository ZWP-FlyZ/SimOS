/*
*
*   从bootloader 跳转到此处，进行一些进行简单的预测
*   并调用 Fmain 函数进入到 内核初始化中。
*   
*   入口处为_Fstart
*/

#include "boot.h"

BOOTSETUP_SEQ = HEADER_IN_SEQ_ADDR # define in boot.h
EMPTY_AREA_SIZE = EMPTY_AREA # 预留空间大小
CONFIG_AREA_SIZE = 128 # 配置区空间大小

# 暂时未使用
code_size = BOOTSETUP_CODE_AREA_SIZE
heap_size = BOOTSETUP_HEAP_AREA_SIZE

# 代码模式 
    .code16gcc 

# 为header 的_Fstart 之前预留一段空闲位置
    .section .headertext,"a"
empty_start:
    # 预留空间 512B 空间
    .fill EMPTY_AREA_SIZE-(.-empty_start),1,0

    .section .header,"ax"
    .global _Fstart
_Fstart:
    jmp start_setup
config_area:
# 预留128配置空间,系统编译配置，以后拓展
    .fill CONFIG_AREA_SIZE-(.-config_area),1,0

    .section .entrytext,"ax"
start_setup: 

# 设置ds,es,fs,gs段寄存器到header起始位置
    movw $BOOTSETUP_SEQ,%ax
    movw %ax,%es
    movw %ax,%ds
    movw %ax,%fs
    movw %ax,%gs
    cld # 设置方向为从小到大

# 设置栈段寄存器，ss,sp。
# 在当前全部可使用的64k（0x0~0xffff）空间,
# 默认栈从偏移0xfffc开始使用向下移动，知道_end标志接触
    movw %ax,%ss
    movw $0xfffc, %sp
    sti

# 设置cs段寄存器到header起始位置
    pushw %ds
    pushw $next
    lretw # 将 cs<-ds,ip<-$next

# setup_sig 在链接器脚本boot.ld 中定义
    cmpl	$0x5a5aaa55, setup_sig
    jne	setup_err
# 初始化bss数据段，代码摘自Linux header.S 
	movw	$__bss_start, %di
	movw	$_end+3, %cx
	xorl	%eax, %eax
	subw	%di, %cx
	shrw	$2, %cx
	rep; stosl



# 启用Fmain来处理进一步的内核初始化代码
# Fmain 不会返回，如果返回需要运行后面的错误代码
next:
    calll Fmain


# Fmain 返回调用puts方法显示错误
setup_err:
#    movl $err_msg,%eax
# 调用puts显示错误信息
#    calll puts

# 以下暂时方法
    mov $err_msg,%si
printLoop:
    mov (%si),%al
    add $0x1,%si
    cmp $0x0,%al
    je  die
    mov $0x0e,%ah
    mov $15,%bx
    int $0x10
    jmp printLoop

    .global die
die:
    hlt
    jmp die
err_msg:
    .string "Fmain returned! ERROR hear!!!"

