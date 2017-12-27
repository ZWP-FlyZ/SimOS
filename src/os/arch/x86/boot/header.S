/*
*
*   从bootloader 跳转到此处，进行一些进行简单的预测
*   并调用 Fmain 函数进入到 内核初始化中。
*   
*   入口处为_Fstart
*/


BOOTSETUP_SEQ = 0x0800 # 
BOOTSETUP_ADDR = 0x8000

DEFAULT_VRAM_ADDR = 0xb8000 # 默认显存位置
EMPTY_AREA_SIZE = 512 # 预留空间大小
CONFIG_AREA_SIZE = 512 # 配置区空间大小

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
# 预留配置空间,系统编译配置，以后拓展


    # boot静态信息
    .global boot_static_info
boot_static_info:
    .string "12345678" # 8Btye,strinfo
    .long BOOTSETUP_ADDR # 内核启动位置,code16_start
    .long 0x10000 # 保护模式代码位置 code32_start


    # boot设置信息，可变动
    .global boot_config_info
boot_config_info:
    .Byte 0 # kbd_status 键盘信息
    # struct screen_info 
    .word 0x1 # vmode 默认80*25 文本模式
    .word 80 # screen_x 横向字符数
    .word 25 # screen_y 纵向行数
    .long (DEFAULT_VRAM_ADDR-BOOTSETUP_ADDR)  # vram 显存 段偏移地址

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
    mov $err_msg,%si
# __stack_chk_fail error jmp hear 
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
    .string "Fmain returned! ERROR hear!!! "
stack_chk_msg:
    .string "stack_chk_fail ERROR!!!"
