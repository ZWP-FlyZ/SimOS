

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
	# $(REMOVE) $(BINTOOLS_PATH)*.*
	# $(REMOVE) $(OUT_PATH)*.*

