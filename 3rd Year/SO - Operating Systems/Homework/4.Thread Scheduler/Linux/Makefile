# Grigore Lucian-Florin - 336CA - Tema 4 SO
CC = gcc
CFLAGS = -fPIC -Wall
LDFLAGS =

.PHONY: build
build: libscheduler.so

libscheduler.so: so_scheduler.o
	$(CC) $(LDFLAGS) -shared -o $@ $^

so_scheduler.o: so_scheduler.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	-rm -f so_scheduler.o libscheduler.so