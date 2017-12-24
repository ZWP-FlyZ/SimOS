
GCC 		= gcc -m16 -c 
LD 		= ld -m elf_i386 
REMOVE	= del  

OBJCOPY = objcopy -R .comment -R .note  


OBJSET = header.o Fmain.o

%.o : %.c makefile
	$(GCC) $*.c -o $*.o

header.o : header.S makefile 
	$(GCC) header.S -o header.o

boot.or :$(OBJSET) boot.ld makefile
	$(LD) $(OBJSET) -T boot.ld  -o boot.or

boot.bin : boot.or makefile
	$(OBJCOPY) boot.or -S -O binary boot.bin

bin  : boot.bin
	make boot.bin
dump : boot.bin makefile
	objdump -m i8086 -D -b binary boot.bin

clean :
	$(REMOVE) *.o *.or *.bin


