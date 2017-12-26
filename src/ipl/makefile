TOOLS_PATH	=	../../bintools
OUT_PATH	=	../../out#SimOS.img输出文件


REMOVE	=	rm -f

MAKE	=	make -r
GCC		=	gcc -m16 -c
OBJCOPY	=	objcopy
BINCOPY=	$(TOOLS_PATH)/bincopy 
OBJDUMP	=	objdump 

STR_ADDR=	0 #截取开始字节数
END_ADDR=	0x200 #截取结束字节数（不包含该位置）

default : 
	$(MAKE) ipl.bin 

ipl.o : ipl.s makefile
	$(GCC)  ipl.s -o ipl.o
ipl.bin : ipl.o makefile
	$(OBJCOPY) -j .boottext -O binary ipl.o ipl.bin
# ipl.bin : ipl.to makefile
# 	$(BINCOPY) ipl.to $(STR_ADDR) $(END_ADDR) ipl.bin

bin : 
	$(MAKE) ipl.bin
clean : 
	$(REMOVE) *.o *.to *.bin

dump : 
	$(OBJDUMP) -D -m i8086 -b binary ipl.bin


