# IOCLA 2016
# USO remembers

CC=gcc
CFLAGS=-m64
ASM=nasm
ASMFLAGS=-f elf64

mainmax: main.o max.o
	$(CC) $(CFLAGS) -o $@ $^
main.o: main.c

max.o: max.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm *.o mainmax
