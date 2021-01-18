CC = g++
CFLAGS = -Wall -g

all: build

build: interpreter

interpreter: interpreter.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

run: build
	./interpreter $(input) $(base)

clean:
	rm -f *.o *~ interpreter
