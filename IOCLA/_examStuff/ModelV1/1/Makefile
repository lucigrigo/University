ASM = nasm
CC = gcc
CFLAGS = -Wall -m32 -Wno-implicit-function-declaration
LDFLAGS = -m32

.PHONY: all clean

all: cross_add

cross_add: cross_add.o macro.o

cross_add.o: cross_add.asm
	$(ASM) -I/usr/share/sasm/include/ -f elf32 -o $@ $<

macro.o: /usr/share/sasm/NASM/macro.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *~
	-rm -f cross_add.o cross_add
