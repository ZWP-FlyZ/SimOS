TOOLS_PATH	=	../../bintools#工具输出路径
OUT_PATH	=	../../out/#SimOS.img输出文件

MAKE	=	make -r
GCC		=	gcc
REMOVE	=	del#in windows

BINCOPY_OBJ = bincopy.o bop.o


default : 
	$(MAKE) all



%.o : %.c makefile
	$(GCC) $*.c -o $*.o -c

bincopy : $(BINCOPY_OBJ)
	$(GCC) $(BINCOPY_OBJ) -o $(TOOLS_PATH)/bincopy

clean : 
	$(REMOVE) *.o 

all : 
	$(MAKE)  bincopy 



