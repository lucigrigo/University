#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int N;
int **a;
int **b;
int **c;

void get_args(int argc, char **argv)
{
	if(argc < 2) {
		printf("Numar insuficient de parametri: ./program N\n");
		exit(1);
	}

	N = atoi(argv[1]);
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
	int i, j, k;

	get_args(argc, argv);
	init();

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < N; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	print(c);

	return 0;
}
