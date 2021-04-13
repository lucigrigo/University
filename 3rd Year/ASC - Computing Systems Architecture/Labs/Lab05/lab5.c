#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double **A;
double **B;
double **C;

int main (void) {
	int i = 0, j = 0, k = 0, n = 1024;

	struct timeval tv1, tv2;
	struct timezone tz;
	double elapsed;

	// alocare memorie pentru matrici
	A = (double **) malloc(n * sizeof(double *));
	B = (double **) malloc(n * sizeof(double *));
	C = (double **) malloc(n * sizeof(double *));

	for(i = 0; i < n; ++i) {
		A[i] = (double *) malloc(n * sizeof(double));
		B[i] = (double *) malloc(n * sizeof(double));
		C[i] = (double *) malloc(n * sizeof(double)); 
	}	

	// initializare valori initiale matrici
	for(i = 0; i < n; ++i) {
		for(j = 0; j < n; ++j) {
			A[i][j] = i + j;
			B[i][j] = (i * j) % 15 ;
			C[i][j] = 0;
		}
	}

	// 0. inmultire de baza
	gettimeofday(&tv1, &tz);
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			for(k = 0; k < n; ++k)
				C[i][j] += A[i][k] * B[k][j];
	gettimeofday(&tv2, &tz);
	elapsed = (double) (tv2.tv_sec - tv1.tv_sec) + (double) (tv2.tv_usec - tv1.tv_usec) * 1.e-6;
	printf("Inmultire de baza: time=%.6fs\n", elapsed);

	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			C[i][j] = 0;

	// 1. constanta in bucla
	gettimeofday(&tv1, &tz);
	for(i = 0; i < n; ++i) {
		for(j = 0; j < n; ++j) {
			register double suma = 0.0;
			for(k = 0; k < n; ++k) {
				suma += A[i][k] * B[k][j];
			}
			C[i][j] = suma;
		}
	}
	gettimeofday(&tv2, &tz);
	elapsed = (double) (tv2.tv_sec - tv1.tv_sec) + (double) (tv2.tv_usec - tv1.tv_usec) * 1.e-6;
	printf("Constanta in bucla: time=%.6fs\n", elapsed);

	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			C[i][j] = 0;

	// 2. accesul la vectori
	gettimeofday(&tv1, &tz);
	for(i = 0; i < n; ++i) {
		double *orig_pa = &A[i][0];
		for(j = 0; j < n; ++j) {
			double *pa = orig_pa;
			double *pb = &B[0][j];
			register double suma = 0.0;
			for(k = 0; k < n; ++k) {
				suma += *pa * *pb;
				pa++;
				pb += n;
			}
			C[i][j] = suma;
		}
	}
	gettimeofday(&tv2, &tz);
	elapsed = (double) (tv2.tv_sec - tv1.tv_sec) + (double) (tv2.tv_usec - tv1.tv_usec) * 1.e-6;
	printf("Accesul la vectori: time=%.6fs\n", elapsed);

	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			C[i][j] = 0;

	// 3. block matrix multiplication
	gettimeofday(&tv1, &tz);
	int bi = 0;
	int bj = 0;
	int bk = 0;
	int blockSize = 64;

	for(bi = 0; bi < n; bi += blockSize)
		for(bj = 0; bj < n; bj += blockSize)
			for(bk = 0; bk < n; bk += blockSize)
				for(i = 0; i < blockSize; ++i)
					for(j = 0; j < blockSize; ++j)
						for(k = 0; k < blockSize; ++k)
							C[bi+i][bj+j] += A[bi+i][bk+k] * B[bk+k][bj+j];

	gettimeofday(&tv2, &tz);
	elapsed = (double) (tv2.tv_sec - tv1.tv_sec) + (double) (tv2.tv_usec - tv1.tv_usec) * 1.e-6;
	printf("BMM: time=%.6fs\n", elapsed);

	// dezalocare memorie
	for(i = 0; i < n; ++i) {
		free(A[i]);
		free(B[i]);
		free(C[i]);
	}
	free(A);
	free(B);
	free(C);

	return 0;
}
