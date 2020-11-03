#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
int N;
int P;
int **a;
int **b;
int **c;

void *thread_function(void *arg)
{
	int thread_id = *(int *)arg;
	int start = thread_id * (double)N / P;
	int end = min((thread_id + 1) * (double)N / P, N);

	// paralelizare inmultire
	for (int i = 0; i < N; i++) {
		for (int j = start; j < end; j++) {
			for (int k = 0; k < N; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	pthread_exit(NULL);
}

void get_args(int argc, char **argv)
{
	if(argc < 3) {
		printf("Numar insuficient de parametri: ./program N P\n");
		exit(1);
	}

	N = atoi(argv[1]);
	P = atoi(argv[2]);
}

void init()
{
	a = malloc(sizeof(int *) * N);
	b = malloc(sizeof(int *) * N);
	c = malloc(sizeof(int *) * N);

	if (a == NULL || b == NULL || c == NULL) {
		printf("Eroare la malloc!");
		exit(1);
	}

	int i, j;
	for (i = 0; i < N; i++) {
		a[i] = malloc(sizeof(int) * N);
		b[i] = malloc(sizeof(int) * N);
		c[i] = malloc(sizeof(int) * N);

		if(a[i] == NULL || b[i] == NULL || c[i] == NULL) {
			printf("Eroare la malloc!");
			exit(1);
		}
	}

	for (i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			c[i][j] = 0;

			if(i <= j) {
				a[i][j] = 1;
				b[i][j] = 1;
			} else {
				a[i][j] = 0;
				b[i][j] = 0;
			}
		}
	}
}

void print(int **mat)
{
	int i, j;

	for (i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%i\t", mat[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	int i;

	get_args(argc, argv);
	init();

	pthread_t tid[P];
	int thread_id[P];

	for (i = 0; i < P; i++) {
		thread_id[i] = i;
		pthread_create(&tid[i], NULL, thread_function, &thread_id[i]);
	}

	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	print(c);

	return 0;
}
