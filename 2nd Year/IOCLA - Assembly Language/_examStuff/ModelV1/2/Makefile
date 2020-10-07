ASM = nasm
CC = gcc
LDFLAGS = -m32

.PHONY: all clean

all: guess_number

guess_number: guess_number.o

guess_number.o: guess_number.asm
	$(ASM) -f elf32 -o $@ $<

clean:
	-rm -f *~
	-rm -f guess_number.o guess_number
