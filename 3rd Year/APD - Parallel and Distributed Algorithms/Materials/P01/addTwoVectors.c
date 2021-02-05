#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "tools.h"
#include "shared.h"

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;

	int start = thread_id * ceil((double)N / P);
	int end = (thread_id + 1) * ceil((double)N / P);
	int i;
	int j;

	// The first for is uselss computationally, we add it because the program is too fast otherwise
	for(j = 0; j < N; j++)
		for(i = start; i < fmin(end, N); i++)
			c[i] = a[i] + b[i];
	return NULL;
}

int main(int argc, char **argv)
{
	getArgs(argc, argv);
	init();

	startThreads(threadFunction);

	print();

	return 0;
}
