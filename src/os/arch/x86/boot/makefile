OBJS_PATH = .

INCLUDE_PATH = ../include/

GCC 	= gcc -m16 -c -I $(INCLUDE_PATH)
LD 		= ld -m elf_i386 
REMOVE	= rm  -f

OBJCOPY = objcopy -R .comment -R .note  

OBJSET = header.o Fmain.o tty.o bioscalls.o ioboot.o

%.o : %.c makefile
	$(GCC)  $*.c -o $(OBJS_PATH)/$*.o

%.o : %.s  makefile 
	$(GCC)  $*.s -o $(OBJS_PATH)/$*.o 

boot.or : $(OBJSET) boot.ld makefile
	$(LD) $(OBJS_PATH)/*.o -T boot.ld  -o $(OBJS_PATH)/boot.or

boot.bin : boot.or makefile
	$(OBJCOPY) $(OBJS_PATH)/boot.or -S -O binary boot.bin

bin  : boot.bin
	make boot.bin
dump : boot.bin makefile
	objdump -m i8086 -D -b binary boot.bin

clean :
	$(REMOVE) *.o *.or *.bin


