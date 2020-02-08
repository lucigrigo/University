ASM = nasm
CC = gcc
CFLAGS = -Wall -m32 -Wno-implicit-function-declaration
LDFLAGS = -m32

.PHONY: all clean

all: bits

bits: bits.o macro.o

bits.o: bits.asm
	$(ASM) -I/usr/share/sasm/include/ -f elf32 -o $@ $<

macro.o: /usr/share/sasm/NASM/macro.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *~
	-rm -f bits.o bits macro.o
