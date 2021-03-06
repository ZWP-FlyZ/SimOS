
ARCH_BOOT_PATH 	= 	./src/os/boot/
#IPL源码路径
IPL_SRC_PATH	=	./src/ipl/
#工具源码的路径
TOOL_SRC_PATH	=	./src/tools/

#工具路径
BINTOOLS_PATH	= 	./bintools/
#镜像路径
OUT_PATH	= 	./out/

REMOVE	=	rm -f
MAKE	=	make -r VERBOSE=1

arcboot:
	$(MAKE) -C $(ARCH_BOOT_PATH) bin
ipl : 
	$(MAKE) -C $(IPL_SRC_PATH) bin
tools : 
	$(MAKE) -C $(TOOL_SRC_PATH) all
	
all : 
	$(MAKE) init_dir
	$(MAKE) tools 
	$(MAKE) ipl
	$(MAKE) arcboot
clean :
	$(REMOVE) $(OUT_PATH)*.img $(OUT_PATH)*.tmp
	$(MAKE) -C $(IPL_SRC_PATH) clean
	$(MAKE) -C $(TOOL_SRC_PATH) clean
	$(MAKE) -C $(ARCH_BOOT_PATH) clean

init_dir :
	if [ ! -d "$(BINTOOLS_PATH)" ]; then mkdir $(BINTOOLS_PATH); fi
	if [ ! -d "$(OUT_PATH)" ]; then mkdir $(OUT_PATH); fi	

BINCREATE = $(BINTOOLS_PATH)bincreate
BINMERGE = $(BINTOOLS_PATH)binmerge

#生成一个512 * 2880 的空镜像文件,将ipl加入
img : all 
	$(BINCREATE) $(OUT_PATH)flopyimg.rim 512 2880 
	$(BINMERGE) $(OUT_PATH)flopyimg.rim $(IPL_SRC_PATH)ipl.bin 0x0 $(OUT_PATH)SimOS.tmp
	$(BINMERGE) $(OUT_PATH)SimOS.tmp $(ARCH_BOOT_PATH)boot.bin 0x200 $(OUT_PATH)SimOS.img
	
QEMU = qemu-system-i386 -L . -m 128

QEMU64 = qemu-system-x86_64 -L . -m 128

run : 
	$(QEMU)  -boot a -fda $(OUT_PATH)SimOS.img

run64 : 
	$(QEMU64) -boot a -fda $(OUT_PATH)SimOS.img

ipsrun :
	$(BINMERGE) $(OUT_PATH)flopyimg.rim $(IPL_SRC_PATH)ipl.bin 0x0 $(OUT_PATH)SimOS.img
	$(QEMU)  -boot a -fda $(OUT_PATH)SimOS.img

