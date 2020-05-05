ASM = nasm
ASM_FLAGS = -I/usr/share/sasm/include/ -f elf32 -g -Fdwarf
CC = gcc
CFLAGS = -Wall -g -m32 -fno-PIC -Wno-implicit-function-declaration
LDFLAGS = -m32 -no-pie

.PHONY: all clean

all: odd_even

odd_even: odd_even.o

odd_even.o: odd_even.asm
	$(ASM) $(ASM_FLAGS) -o $@ $<

clean:
	-rm -f *~
	-rm -f odd_even.o odd_even
