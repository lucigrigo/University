.phony: build test clean

TESTSRC = $(wildcard test*.c)
TEST = $(patsubst %.c,%,$(TESTSRC))
TEST_STACK =  $(wildcard *Stack)
TEST_QUEUE =  $(wildcard *Queue)

SRC = $(foreach src,$(wildcard *c),$(patsubst test%,,$(src)))
EXEC = $(patsubst %.c,%,$(SRC))

HEADERS = $(wildcard *.h)

CC = gcc
CC_FLAGS = -std=c9x -g -O0
LDFLAGS=-lm

build: $(EXEC) $(TEST)

test-stack: $(TEST_STACK)
	valgrind --leak-check=full ./$(TEST_STACK)

test-queue: $(TEST_QUEUE)
	valgrind --leak-check=full ./$(TEST_QUEUE)

$(EXEC):%:%.c $(HEADERS)
	$(CC) $(CC_FLAGS) $(firstword $+) -o $@ $(LDFLAGS)

$(TEST):%:%.c $(HEADERS)
	$(CC) $(CC_FLAGS) $(firstword $+) -o $@ $(LDFLAGS)

clean:
	rm -f $(EXEC) $(TEST)