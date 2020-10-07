CFLAGS = -Wall -m32 -fno-stack-protector -mpreferred-stack-boundary=2 -fno-PIC
LDFLAGS = -m32 -no-pie

.PHONY: all clean

all: test

test: test.o hidden.o

test.o: test.c

clean:
	-rm -f *~
	-rm -f test.o test
