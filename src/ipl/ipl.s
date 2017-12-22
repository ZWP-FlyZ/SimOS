    .code16
    .text
#地址偏远的原方法，现在使用新的方法并更改bincopy的参数
#    .org 0x7c00

BOOTSEQ = 0x07c0
BOOTADDR = 0x7c00

bootse:
    ljmp $BOOTSEQ,$entry
    .byte 0x90
    .ascii "SimOS   " #启动盘名称(8Byte)
    .word 512    #扇区大小
    .byte 0x01      #簇大小
    .word 1      #FAT起始扇区
    .byte 0x02      #FAT表个数
    .word 224       #根目录大小
    .word 2880      #磁盘扇区大小
    .byte 0xf0      #磁盘种类
    .word 9         #FAT长度
    .word 18        #1个磁道扇区数
    .word 2         #磁头数
    .long 0         
    .long 2880
    .byte 0,0,0x29
    .long 0xffffffff
    .ascii "SimOS_IMG  "    #磁盘名称(11Byte)
    .ascii "FAT12   "       #磁盘格式名称(8Byte)
    .fill 18,1,0         

entry:
    mov $0x0,%ax
    mov %ax,%ss
    mov BOOTADDR,%sp
    mov %ax,%ds
    mov %ax,%es
    mov $BOOTADDR,%ax
    add $msg,%ax
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

msg:
    .asciz "\n\n hello zwp \n"
code_end:
    .set code_size,code_end - bootse
    .set space_size,510 - code_size
    .fill space_size,1,0
    .byte 0x55,0xaa
