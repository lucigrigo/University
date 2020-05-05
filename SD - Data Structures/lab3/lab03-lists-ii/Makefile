.phony: build test test-problem clean

TESTSRC = $(wildcard test*.c)
TEST = $(patsubst %.c,%,$(TESTSRC))

PROBSRC = problem.c
TESTPROB = $(patsubst %.c,%,$(PROBSRC))

SRC = $(foreach src,$(wildcard *c),$(patsubst test%,,$(src)))
EXEC = $(patsubst %.c,%,$(SRC))

HEADERS = $(wildcard *.h)

CC = gcc
CC_FLAGS = -std=c9x -g -O0

build: $(EXEC) $(TEST)

test: $(TEST)
	valgrind --leak-check=full ./$(TEST)

test-problem: $(TESTPROB)
	valgrind --leak-check=full ./$(TESTPROB)

$(EXEC):%:%.c $(HEADERS)
	$(CC) $(CC_FLAGS) $(firstword $+) -o $@

$(TEST):%:%.c $(HEADERS)
	$(CC) $(CC_FLAGS) $(firstword $+) -o $@

clean:
	rm -f $(EXEC) $(TEST)
