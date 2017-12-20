#IPL源码路径
IPL_SRC_PATH	=	./src/ipl/
#工具源码的路径
TOOL_SRC_PATH	=	./src/tools/

#工具路径
BINTOOLS_PATH	= 	./bintools/
#镜像路径
OUT_PATH	= 	./out/

REMOVE	=	del#in windows
MAKE	=	make -r VERBOSE=1

ipl : 
	$(MAKE) -C $(IPL_SRC_PATH) bin

tools : 
	$(MAKE) -C $(TOOL_SRC_PATH) all
	
all : 
	$(MAKE) tools 
	$(MAKE) ipl 
clean :  
	$(MAKE) -C $(IPL_SRC_PATH) clean
	$(MAKE) -C $(TOOL_SRC_PATH) clean

BINCREATE = $(BINTOOLS_PATH)bincreate
BINMERGE = $(BINTOOLS_PATH)binmerge

#生成一个512 * 2880 的空镜像文件,将ipl加入
img : 
	$(BINCREATE) $(OUT_PATH)flopyimg.rim 512 2880 
	$(BINMERGE) $(OUT_PATH)flopyimg.rim $(IPL_SRC_PATH)ipl.bin 0x0 $(OUT_PATH)SimOS.img

QEMU = qemu-system-i386
QEMU64 = qemu-system-x86_64

run : 
	$(QEMU) $(OUT_PATH)SimOS.img

run64 : 
	$(QEMU64) $(OUT_PATH)SimOS.img

