/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	/* alocare memorie pentru matrici */
	double *C = (double *) calloc(N * N, sizeof(double));
        if (C == NULL) exit(-1);

        double *D = (double *) calloc(N * N, sizeof(double));
        if (D == NULL) exit(-1);

	register int i, j, k;
	
	/* C = A x B */
	for (i = 0; i < N; ++i) {
		register double *c_ptr = C + i * N; /* linia i din C */
		register double *a_ptr_orig = A + i * N + i; /* linia i + coloana i din A */

		for (j = 0; j < N; ++j) {
			register double s = 0; /* unde va fi calulata suma */
			register double *a_ptr = a_ptr_orig;
			register double *b_ptr = B + i * N + j; /* linia i si coloana j din B */
		
			for (k = i; k < N; ++k) {
				s += *a_ptr * *b_ptr;
				a_ptr++;
				b_ptr += N;
			}

			*c_ptr = s;
			c_ptr++;
		}
	}

	/* D = C x B' */
	for (i = 0; i < N; ++i) {
		register double *d_ptr = D + i * N; /* linia i din D */
		register double *c_ptr_orig = C + i * N; /* linia i din C */

		for (j = 0; j < N; ++j) {
			register double s = 0; /* unde va fi calculata suma */
			register double *c_ptr = c_ptr_orig;
			register double *bt_ptr = B + j * N; /* linia j din B */

			for (k = 0; k < N; ++k) {
				s += *c_ptr * *bt_ptr;
				c_ptr++;
				bt_ptr++;
			}

			*d_ptr = s;
			d_ptr++;
		}
	}

	/* D += A' x A */
	for (i = 0; i < N; ++i) {
		register double *d_ptr = D + i * N; /* linia i din D */
		register double *at_ptr_orig = A + i; /* coloana i din A */

		for (j = 0; j < N; ++j) {
			register double s = 0; /* unde va fi calculata suma */
			register double *at_ptr = at_ptr_orig;
			register double *a_ptr = A + j; /* coloana j din A */

			for (k = 0; k <= j; ++k) {
				s += *at_ptr * *a_ptr;
				at_ptr += N;
				a_ptr += N;
			}

			*d_ptr = *d_ptr + s;
			d_ptr++;
		}
	}

	free(C);
	
	return D;	
}
