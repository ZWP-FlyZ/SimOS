

AS 		= gcc -m16 -c
LD 		= ld -m elf_i386 
REMOVE	= del  


OBJCOPY = objcopy -R .comment -R .note  

header.o : header.S makefile 
	$(AS) header.S -o header.o

boot.or : header.o boot.ld makefile
	$(LD) header.o -T boot.ld  -o boot.or

boot.bin : boot.or makefile
	$(OBJCOPY) boot.or -S -O binary boot.bin

bin  : boot.bin
	make boot.bin
dump : boot.bin makefile
	objdump -m i8086 -D -b binary boot.bin

clean :
	$(REMOVE) *.o *.or *.bin


