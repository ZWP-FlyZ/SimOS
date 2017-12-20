#工具输出路径
TOOLS_PATH	=	../../bintools
#SimOS.img输出文件
OUT_PATH	=	../../out/

MAKE	=	make -r VERBOSE=1 
GCC		=	gcc
REMOVE	=	del#in windows

DEPEND_OBJ	= bop.o fop.o
BINCOPY_OBJ = $(DEPEND_OBJ) bincopy.o
BINCREATE_OBJ = $(DEPEND_OBJ) bincreate.o
BINMERGE_OBJ = $(DEPEND_OBJ) binmerge.o

default : 
	$(MAKE) all

%.o : %.c makefile
	$(GCC) $*.c -o $*.o -c

bincopy : $(BINCOPY_OBJ)
	$(GCC) $(BINCOPY_OBJ) -o $(TOOLS_PATH)/bincopy
bincreate : $(BINCREATE_OBJ)
	$(GCC) $(BINCREATE_OBJ) -o $(TOOLS_PATH)/bincreate
binmerge : $(BINMERGE_OBJ)
	$(GCC) $(BINMERGE_OBJ) -o $(TOOLS_PATH)/binmerge

clean : 
	$(REMOVE) *.o 

all : 
	$(MAKE)  bincopy 
	$(MAKE)  bincreate
	$(MAKE)  binmerge

