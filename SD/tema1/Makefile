.phony: build test clean

SRC = tema1.c
EXEC = $(patsubst %.c,%,$(SRC))

HEADERS = $(wildcard *.h)

CC = gcc
CC_FLAGS = -std=c9x -g -O0 -Wall
LDFLAGS=-lm

build: $(EXEC)

test: $(EXEC)
	./$(EXEC)

test-valgrind: $(EXEC)
	valgrind --leak-check=full ./$(EXEC)

$(EXEC):%:%.c $(HEADERS)
	$(CC) $(CC_FLAGS) $(firstword $+) -o $@ $(LDFLAGS)

clean:
	rm -f $(EXEC) *.out