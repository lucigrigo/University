CC=gcc
CFLAGS=-I -Wall

build: client.c buffers.c helpers.c parson.c
	$(CC) -o client client.c buffers.c parson.c helpers.c $(FLAGS)

run: client
	./client

clean:
	rm -f *.o client