CFLAGS=-m32
AFLAGS=-f elf

build: tema1

tema1: tema1.o includes/ASTUtils.o includes/macro.o
	gcc $^ -o $@ $(CFLAGS)

tema1.o: tema1.asm
	nasm $^ -o $@ $(AFLAGS)

clean:
	rm -rf tema1.o tema1