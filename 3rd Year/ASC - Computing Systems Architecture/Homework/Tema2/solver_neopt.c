/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	/* alocare memorie pentru matrici */
	double *C = (double *) calloc(N * N, sizeof(double));
	if (C == NULL) exit(-1);
	
	double *D = (double *) calloc(N * N, sizeof(double));
	if (D == NULL) exit(-1);

	int i, j, k;
	
	/* C = A x B */
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			for (k = i; k < N; ++k)
				C[i * N + j] += A[i * N + k] * B[k * N + j];

	/* D = C * B' */
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			for (k = 0; k < N; ++k)
				D[i * N + j] += C[i * N + k] * B[j * N + k];

	/* D += A' x A */
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			for (k = 0; k <= j; ++k)
				D[i * N + j] += A[k * N + i] * A[k * N + j];
	
	free(C);

	return D;
}
