.phony: build run test clean

CC = gcc
CFLAGS= -Wall -std=c99
DEPS = $(wildcard *.h)
OBJ = $(patsubst %.c,%.o,$(wildcard *.c))
EXEC = testGraph

build: $(EXEC)
		
$(EXEC):$(OBJ)
	gcc $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c  $< -o $@ 

run:
	./$(EXEC)

test:
	valgrind --leak-check=full ./$(EXEC)

clean:
	rm -f $(EXEC) $(OBJ)
