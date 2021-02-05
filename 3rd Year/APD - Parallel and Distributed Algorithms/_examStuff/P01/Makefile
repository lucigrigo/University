all: useAllCPU addTwoVectors

useAllCPU: useAllCPU.c
	gcc -o useAllCPU useAllCPU.c -lpthread -lm

addTwoVectors: addTwoVectors.c
	gcc -o addTwoVectors par.c tools.c shared.c addTwoVectors.c -lpthread -lm