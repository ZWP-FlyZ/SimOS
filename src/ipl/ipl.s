

# boot起始段地址
BOOTSEQ = 0x07c0
# boot起始线地址
BOOTADDR = 0x7c00

# header.S 代码被导入内存中的段值与偏移量
HEADER_IN_SEQ_ADDR =  0x0800
HEADER_IN_OFF_ADDR =  0x0

# entry偏移地址
START_ENTRY_OFFSET = 0x20
START_ENTRY_IN_SEQ_ADDR = HEADER_IN_SEQ_ADDR + START_ENTRY_OFFSET


# 读取柱面数，第一柱面
CYLS = 10

# 错误读取计数
ERR_READ_COUT = 5 

    .code16gcc
    .section .boottext,"ax"
    .global bootse
bootse:
    ljmp $BOOTSEQ,$entry
    .byte 0x90
    .ascii "SimOS   " # 启动盘名称(8Byte)
    .word 512    # 扇区大小
    .byte 0x01      # 簇大小
    .word 1      # FAT起始扇区
    .byte 0x02      # FAT表个数
    .word 224       # 根目录大小
    .word 2880      # 磁盘扇区大小
    .byte 0xf0      # 磁盘种类
    .word 9         # FAT长度
    .word 18        # 1个磁道扇区数
    .word 2         # 磁头数
    .long 0         
    .long 2880
    .byte 0,0,0x29
    .long 0xffffffff
    .ascii "SimOS_IMG  "    # 磁盘名称(11Byte)
    .ascii "FAT12   "       # 磁盘格式名称(8Byte)
    .fill 18,1,0         

entry:
    mov $0,%ax
    mov %ax,%ss
    mov %ax,%ds
    mov $0x7c00,%sp

# 读取之后的扇区数据，注意以下方法可能只适合软盘读取方式

    mov $HEADER_IN_SEQ_ADDR,%ax # 设定起始段位置
    mov %ax,%es
    mov $0,%ch # 柱面号
    mov $0,%dh # 磁头号
    mov $2,%cl # 扇区号

readloop:
    mov $0,%si # 重置错误读取计数

retry:
    mov $0x2,%ah # 设置读取操作标记
    mov $0x1,%al # 单次读取扇区数
    mov $0x0,%bx # 读入偏移地址
    mov $0x0,%dl # 设置磁盘号
    int $0x13 # 磁盘中断
    jnc next # 读取正确，carry位为0
    add $1,%si
    cmp $ERR_READ_COUT,%si
    je  err
    mov $0x0,%ah # 重置磁盘操作标记
    mov $0x0,%dl # 设置磁盘号
    int $0x13 # 磁盘中断
    jmp retry

next:
    mov %es,%ax
    add $0x0020,%ax
    mov %ax,%es
    add $0x1,%cl # 扇区号增加
    cmp $18,%cl # 是否为最后一个扇区
    jbe readloop
    mov $1,%cl # 还原扇区号
    add $1,%dh # 更换磁头
    cmp $2,%dh # 是否为最后一个磁头
    jb readloop
    mov $0,%dh # 还原柱头号
    add $1,%ch # 增加柱面号
    cmp $CYLS,%ch
    jb readloop

# 跳转到header.S 启动内核
    jmpl $START_ENTRY_IN_SEQ_ADDR,$HEADER_IN_OFF_ADDR 

; prtboot:
;     mov $0x8000,%si
;     mov $0x0,%cx
; pbloop:
;     mov (%si),%al
;     add $0x1,%si
;     add $0x1,%cx
;     cmp $0x400,%cx
;     je  err
;     mov $0x0e,%ah
;     mov $15,%bx
;     int $0x10
;     jmp pbloop
           
err:
    mov $BOOTADDR,%ax
    add $err_msg,%ax
    mov %ax,%si
printLoop:
    mov (%si),%al
    add $0x1,%si
    cmp $0x0,%al
    je  fin
    mov $0x0e,%ah
    mov $15,%bx
    int $0x10
    jmp printLoop
fin:
    hlt
    jmp fin

err_msg:
    .asciz "\n read error !\n"
code_end:
    .fill 510-(.-bootse),1,0 # 补全剩余字符
    .byte 0x55,0xaa # 标记启动扇区
