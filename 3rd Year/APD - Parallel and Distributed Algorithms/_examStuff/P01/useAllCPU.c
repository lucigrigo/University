#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>


int P;
int N;
int NReps;
int printLevel;

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

void getArgs(int argc, char **argv)
{
	if(argc < 5) {
		printf("Not enough paramters: ./useAllCPU N NReps printLevel P\nprintLevel: 0=no, 1=some, 2=verbouse\nP: number of threads\n");
		exit(1);
	}
	N = atoi(argv[1]);
	NReps = atoi(argv[2]);
	printLevel = atoi(argv[3]);
	P = atoi(argv[4]);
}

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;
	int i, j;
	double aux=5;

	for(j = 0; j < NReps; j++)
		for(i = 0; i < N/P; i++)
			aux = sqrt(aux);
	return NULL;
}

void init()
{
}

void printPartial()
{
	printf("Nothing to print\n");
}

void printAll()
{
	printf("Nothing to print\n");
}

void print()
{
	
	if(printLevel == 0)
		return;
	if(printLevel == 1) {
		printPartial();
	} else {
		printAll();
	}
}

int main(int argc, char **argv)
{
	int i;
	getArgs(argc, argv);
	init();

	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;

	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	print();

	return 0;
}
