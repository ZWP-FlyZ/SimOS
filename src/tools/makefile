TOOLS_PATH	=	../../bintools#工具输出路径
OUT_PATH	=	../../out/#SimOS.img输出文件

MAKE	=	make -r
GCC		=	gcc
REMOVE	=	del#in windows

BINSPLIT_OBJ = binsplit.o bop.o


default : 
	$(MAKE) all



%.o : %.c makefile
	$(GCC) $*.c -o $*.o -c

binsplit : $(BINSPLIT_OBJ)
	$(GCC) $(BINSPLIT_OBJ) -o $(TOOLS_PATH)/binsplit

clean : 
	$(REMOVE) *.o 

all : 
	$(MAKE)  binsplit



