TOOLS_PATH	=	../../bintools
OUT_PATH	=	../../out#SimOS.img输出文件


REMOVE	=	del#in windows

MAKE	=	make -r
AS		=	as
OBJCOPY	=	objcopy
BINSPLIT=	$(TOOLS_PATH)/binsplit 
OBJDUMP	=	objdump 

STR_ADDR=	0x7c00 #截取开始字节数
END_ADDR=	0x7e00 #截取结束字节数（不包含该位置）

default : 
	$(MAKE) ipl.bin 

ipl.o : ipl.s makefile
	$(AS) -32 ipl.s -o ipl.o
ipl.to : ipl.o makefile
	$(OBJCOPY) -R .note -R .comment -S -O binary ipl.o ipl.to
ipl.bin : ipl.to makefile
	$(BINSPLIT) ipl.to $(STR_ADDR) $(END_ADDR) ipl.bin

bin : 
	$(MAKE) ipl.bin
clean : 
	$(REMOVE) ipl.o ipl.to ipl.bin


