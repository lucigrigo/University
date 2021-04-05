# Grigore Lucian-Florin
# 336CA
# Sisteme de Operare
# Tema 1 - Multi-platform development
default=build

build: tema1.o hashmap.o utils.o strtok_saved.o
	gcc tema1.o hashmap.o utils.o strtok_saved.o -o so-cpp

tema1.o: tema1.c
	gcc -g -Wall -std=c89 -c tema1.c

hashmap.o: hashmap.c
	gcc -g -Wall -std=c89 -c hashmap.c

utils.o: utils.c
	gcc -g -Wall -std=c89 -c utils.c

strtok_saved.o: strtok_saved.c
	gcc -g -Wall -std=c89 -c strtok_saved.c

clean:
	rm *.o
	rm so-cpp
