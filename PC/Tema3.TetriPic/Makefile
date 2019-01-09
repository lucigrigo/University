CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99
HEADERS = bmp_header.h
OBJECTS = main.o
EXEC = tetris

.PHONY = default build clean

default: build

build: tetris

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

run_task1: build
	./$(EXEC) 1

run_task2: build
	./$(EXEC) 2

run_task3: build
	./$(EXEC) 3

run_task4: build
	./$(EXEC) 4

run_bonus: build
	./$(EXEC) b

clean:
	-rm -f $(OBJECTS)
	-rm -f $(EXEC)
