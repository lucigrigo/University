								#			Curs : Programarea Calculatoarelor
								#			Tema 2 - Formatare Text
								#			Nume si prenume : Grigore Lucian-Florin
								# 		Grupa : 314CD

CC = gcc
CFLAGS = -g -Wall
HEADERS =
OBJECTS = tema2.o
EXEC = format_text

.PHONY = default build clean

default: build

build: format_text

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

run: build
	./$(EXEC) ${ARGS}

clean:
	-rm -f $(OBJECTS)
	-rm -f $(EXEC)
