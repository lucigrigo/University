// Grigore Lucian-Florin - 336CAb
// APD - Laborator 3 - Task 3 & 4 
// (afisarea terminalului este dupa cod, in acest fisier) 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "pthread_barrier_mac.h"

int L; // latura matricei
int N; // numarul de elemente de sortat
int P;
int *v;
int *vQSort;
int **M;
pthread_barrier_t barrier; // bariera folosita

void compare_vectors(int *a, int *b) {
	int i;

	for (i = 0; i < N; i++) {
		if (a[i] != b[i]) {
			printf("Sortare incorecta\n");
			return;
		}
	}

	printf("Sortare corecta\n");
}

void display_vector(int *v) {
	int i;
	int display_width = 2 + log10(N);

	for (i = 0; i < N; i++) {
		printf("%*i", display_width, v[i]);
	}

	printf("\n");
}

void display_matrix(int **M) {
	int i, j;
	int display_width = 2 + log10(N);

	for (i = 0; i < L; i++) {
		for (j = 0; j < L; j++) {
			printf("%*i", display_width, M[i][j]);
		}
		printf("\n");
	}
}

void copy_matrix_in_vector(int *v, int **M) {
	int i, j;
	for (i = 0; i < L; i++) {
		if (i % 2 == 0) {
			for (j = 0; j < L; j++) {
				v[i * L + j] = M[i][j];
			}
		} else {
			for (j = L; j > 0; j--) {
				v[i * L + (L - j)] = M[i][j-1];
			}
		}
	}
}

int cmp(const void *a, const void *b) {
	int A = *(int*)a;
	int B = *(int*)b;
	return A - B;
}

int cmpdesc(const void *a, const void *b) {
	int A = *(int*)a;
	int B = *(int*)b;
	return B - A;
}

void get_args(int argc, char **argv)
{
	if(argc < 3) {
		printf("Numar insuficient de parametri: ./shear L P (L = latura matricei)\n");
		exit(1);
	}

	L = atoi(argv[1]);
	N = L * L;
	P = atoi(argv[2]);
}

void init()
{
	int i, j;
	v = malloc(sizeof(int) * N);
	vQSort = malloc(sizeof(int) * N);
	M = malloc(sizeof(int*) * L);

	if (v == NULL || vQSort == NULL || M == NULL) {
		printf("Eroare la malloc!");
		exit(1);
	}

	for (i = 0; i < L; i++) {
		M[i] = malloc(sizeof(int) * L);
	}

	srand(42);

	for (i = 0; i < L; i++) {
		for (j = 0; j < L; j++) {
			M[i][j] = rand() % N;
		}
	}
}

void print()
{
	printf("M:\n");
	display_matrix(M);

	copy_matrix_in_vector(v, M);
	printf("v:\n");
	display_vector(v);
	printf("vQSort:\n");
	display_vector(vQSort);
	compare_vectors(v, vQSort);	
}

void *thread_function(void *arg)
{
	int thread_id = *(int *)arg;

    for(int k = 0; k < log(N) + 1; ++k) {
        for(int i = thread_id; i < L; i += P) {
            if (i % 2) {
                qsort(M[i], L, sizeof(int), cmpdesc);
            } else {
                qsort(M[i], L, sizeof(int), cmp);
            }
        }

        // bariera
        pthread_barrier_wait(&barrier);

        for (int i = thread_id; i < L; i += P) {
            int aux[L];
            for (int j = 0; j < L; j++) {
                aux[j] = M[j][i];
            }
            
            qsort(aux, L, sizeof(int), cmp);

            for (int j = 0; j < L; j++) {
                M[j][i] = aux[j];
            }
        }

        // bariera
        pthread_barrier_wait(&barrier);
    }

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	get_args(argc, argv);
	init();

	int i;
	pthread_t tid[P];
	int thread_id[P];

    // initializare bariera
    pthread_barrier_init(&barrier, NULL, P);

	// se sorteaza etalonul
	copy_matrix_in_vector(vQSort, M);
	qsort(vQSort, N, sizeof(int), cmp);

	// se creeaza thread-urile
	for (i = 0; i < P; i++) {
		thread_id[i] = i;
		pthread_create(&tid[i], NULL, thread_function, &thread_id[i]);
	}

	// se asteapta thread-urile
	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	// shear sort clasic - trebuie paralelizat
	// for (k = 0; k < log(N) + 1; k++) {
	// 	// se sorteaza liniile pare crescator
	// 	// se sorteaza liniile impare descrescator
	// 	for (i = 0; i < L; i++) {
	// 		if (i % 2) {
	// 			qsort(M[i], L, sizeof(int), cmpdesc);
	// 		} else {
	// 			qsort(M[i], L, sizeof(int), cmp);
	// 		}
	// 	}

	// 	// se sorteaza coloanele descrescator
	// 	for (i = 0; i < L; i++) {
	// 		for (j = 0; j < L; j++) {
	// 			aux[j] = M[j][i];
	// 		}

	// 		qsort(aux, L, sizeof(int), cmp);

	// 		for (j = 0; j < L; j++) {
	// 			M[j][i] = aux[j];
	// 		}
	// 	}
	// }

	// se afiseaza matricea
	// se afiseaza vectorul etalon
	// se afiseaza matricea curenta sub forma de vector
	// se compara cele doua
	print();

	free(v);
	free(vQSort);
	for (i = 0; i < L; i++) {
		free(M[i]);
	}
	free(M);

    // dezalocare bariera
    pthread_barrier_destroy(&barrier);

	return 0;
}

/*
------------------------------------ SCALABILITATE PROGRAM

Observatie: am un procesor cu 6 core-uri.

------------------------------------

(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 1

real	0m1.122s
user	0m1.113s
sys	0m0.006s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 1

real	0m1.117s
user	0m1.109s
sys	0m0.005s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 1

real	0m1.129s
user	0m1.120s
sys	0m0.006s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 1

real	0m1.105s
user	0m1.096s
sys	0m0.005s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 1

real	0m1.101s
user	0m1.093s
sys	0m0.004s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 1

real	0m1.106s
user	0m1.098s
sys	0m0.005s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 1

real	0m1.116s
user	0m1.108s
sys	0m0.005s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 2

real	0m0.608s
user	0m1.184s
sys	0m0.005s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 2

real	0m0.617s
user	0m1.201s
sys	0m0.005s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 2

real	0m0.606s
user	0m1.179s
sys	0m0.005s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 2

real	0m0.622s
user	0m1.213s
sys	0m0.006s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 2

real	0m0.623s
user	0m1.214s
sys	0m0.005s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 2

real	0m0.607s
user	0m1.178s
sys	0m0.005s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 2

real	0m0.616s
user	0m1.203s
sys	0m0.005s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 2

real	0m0.616s
user	0m1.202s
sys	0m0.005s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 4

real	0m0.335s
user	0m1.250s
sys	0m0.007s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 4

real	0m0.336s
user	0m1.258s
sys	0m0.006s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 4

real	0m0.344s
user	0m1.277s
sys	0m0.006s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 4

real	0m0.335s
user	0m1.253s
sys	0m0.006s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 4

real	0m0.339s
user	0m1.265s
sys	0m0.006s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 4

real	0m0.340s
user	0m1.271s
sys	0m0.006s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 4

real	0m0.334s
user	0m1.246s
sys	0m0.006s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 4

real	0m0.332s
user	0m1.239s
sys	0m0.006s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 4

real	0m0.334s
user	0m1.247s
sys	0m0.006s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 6

real	0m0.241s
user	0m1.293s
sys	0m0.007s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 6

real	0m0.250s
user	0m1.330s
sys	0m0.008s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 6

real	0m0.248s
user	0m1.325s
sys	0m0.007s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 6

real	0m0.241s
user	0m1.295s
sys	0m0.007s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 6

real	0m0.240s
user	0m1.281s
sys	0m0.007s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 6

real	0m0.242s
user	0m1.295s
sys	0m0.007s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 6

real	0m0.239s
user	0m1.294s
sys	0m0.006s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 6

real	0m0.240s
user	0m1.284s
sys	0m0.007s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 8

real	0m0.220s
user	0m1.496s
sys	0m0.008s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 8

real	0m0.222s
user	0m1.495s
sys	0m0.009s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 8

real	0m0.226s
user	0m1.527s
sys	0m0.010s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 8

real	0m0.220s
user	0m1.477s
sys	0m0.008s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 8

real	0m0.222s
user	0m1.485s
sys	0m0.008s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 8

real	0m0.221s
user	0m1.497s
sys	0m0.009s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 8

real	0m0.222s
user	0m1.488s
sys	0m0.008s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 8

real	0m0.221s
user	0m1.493s
sys	0m0.008s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 12

real	0m0.213s
user	0m1.724s
sys	0m0.010s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 12

real	0m0.214s
user	0m1.740s
sys	0m0.009s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 12

real	0m0.214s
user	0m1.713s
sys	0m0.010s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 12

real	0m0.205s
user	0m1.744s
sys	0m0.009s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 12

real	0m0.212s
user	0m1.739s
sys	0m0.010s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 12

real	0m0.209s
user	0m1.737s
sys	0m0.010s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 12

real	0m0.215s
user	0m1.682s
sys	0m0.009s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 12

real	0m0.206s
user	0m1.736s
sys	0m0.010s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 16

real	0m0.217s
user	0m1.672s
sys	0m0.011s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 16

real	0m0.212s
user	0m1.634s
sys	0m0.011s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 16

real	0m0.212s
user	0m1.626s
sys	0m0.011s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 16

real	0m0.215s
user	0m1.648s
sys	0m0.012s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 16

real	0m0.215s
user	0m1.642s
sys	0m0.012s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 16

real	0m0.223s
user	0m1.635s
sys	0m0.011s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./shear 1024 16

real	0m0.221s
user	0m1.625s
sys	0m0.011s
*/
