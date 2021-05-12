/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <cblas.h>

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	/* alocare memorie pentru matrici */
	double *C = (double *) calloc(N * N, sizeof(double));
	if (C == NULL) exit(-1);

	double *D = (double *) calloc(N * N, sizeof(double));
	if (D == NULL) exit(-1);

	/* C = A x B */
	memcpy(C, B, N * N * sizeof(double));	

	cblas_dtrmm(
		CblasRowMajor,
		CblasLeft,
		CblasUpper,
		CblasNoTrans,
		CblasNonUnit,
		N,
		N,
		1.0,
		A,
		N,
		C,
		N
	);	

	/* D = C x B' */
	cblas_dgemm(
		CblasRowMajor,
		CblasNoTrans,
		CblasTrans,
		N,
		N,
		N,
		1.0,
		C,
		N,
		B,
		N,
		0.0,
		D,
		N
	);


	/* D += A' x A */
	cblas_dgemm(
		CblasRowMajor,
		CblasTrans,
		CblasNoTrans,
		N,
		N,
		N,
		1.0,
		A,
		N,
		A,
		N,
		1.0,
		D,
		N
	);

	free(C);

	return D;
}
