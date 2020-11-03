// Grigore Lucian-Florin - 336CAb
// APD - Laborator 3 - Task 1 & 2 
// (afisarea terminalului este dupa cod, in acest fisier) 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "pthread_barrier_mac.h"
#define min(a, b) ((a) < (b) ? (a) : (b))

int N;
int P;
int *v;
int *vQSort;
pthread_barrier_t barrier;

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

int cmp(const void *a, const void *b) {
	int A = *(int*)a;
	int B = *(int*)b;
	return A - B;
}

void get_args(int argc, char **argv)
{
	if(argc < 3) {
		printf("Numar insuficient de parametri: ./oets N P\n");
		exit(1);
	}

	N = atoi(argv[1]);
	P = atoi(argv[2]);
}

void init()
{
	int i;
	v = malloc(sizeof(int) * N);
	vQSort = malloc(sizeof(int) * N);

	if (v == NULL || vQSort == NULL) {
		printf("Eroare la malloc!");
		exit(1);
	}

	srand(42);

	for (i = 0; i < N; i++)
		v[i] = rand() % N;
}

void print()
{
	printf("v:\n");
	display_vector(v);
	printf("vQSort:\n");
	display_vector(vQSort);
	compare_vectors(v, vQSort);
}

void *thread_function(void *arg)
{
	int thread_id = *(int *)arg;

	// implementati aici OETS paralel
    int start = thread_id * (double) N / P;
    int end = min(N, (thread_id + 1) * (double) N / P);

    int start_even = (start % 2 == 1) ? start + 1 : start;
    int start_odd = (start % 2 == 1) ? start : start + 1;

    for(int i = 0; i < N; ++i) {
        for(int j = start_even; j < end && (i < N - 1); j += 2) {
            if(v[j] > v[j + 1]) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }

        // bariera
        pthread_barrier_wait(&barrier);

        for(int j = start_odd; j < end && j < (N - 1); j += 2) {
            if(v[j] > v[j + 1]) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
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
    // initializare bariera
    pthread_barrier_init(&barrier, NULL, P);

	int i;
	pthread_t tid[P];
	int thread_id[P];

	// se sorteaza vectorul etalon
	for (i = 0; i < N; i++)
		vQSort[i] = v[i];
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

	// bubble sort clasic - trebuie transformat in OETS si paralelizat
	// int sorted = 0;
	// while (!sorted) {
	// 	sorted = 1;

	// 	for (i = 0; i < N-1; i++) {
	// 		if(v[i] > v[i + 1]) {
	// 			aux = v[i];
	// 			v[i] = v[i + 1];
	// 			v[i + 1] = aux;
	// 			sorted = 0;
	// 		}
	// 	}
	// }

	// se afiseaza vectorul etalon
	// se afiseaza vectorul curent
	// se compara cele doua
	print();

	free(v);
	free(vQSort);

    // dezalocare bariera
    pthread_barrier_destroy(&barrier);

	return 0;
}

/*
---------------------------- SCALABILITATE PROGRAM

Observatie:
Am rulat programul folosind 10.000 de elemente in vector.
Scalabilitatea este insemnata atunci cand se compara utilizarea a 1, 2 sau 4 thread-uri.
La 8 thread-uri nu se poate remarca nicio imbunatatire.
Procesorul meu are 6 core-uri, de aceea pe 6 thread-uri programul se executa mai rapid
decat daca as folosi 8 thread-uri.
La rularea a 12 sau chiar 16 thread-uri, se observa ineficienta. 

----------------------------

(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 1

real	0m0.690s
user	0m0.309s
sys	0m0.003s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 1

real	0m0.323s
user	0m0.319s
sys	0m0.002s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 1

real	0m0.329s
user	0m0.324s
sys	0m0.003s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 1

real	0m0.325s
user	0m0.321s
sys	0m0.002s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 1

real	0m0.324s
user	0m0.320s
sys	0m0.003s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 1

real	0m0.322s
user	0m0.317s
sys	0m0.003s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 1

real	0m0.327s
user	0m0.321s
sys	0m0.003s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 2

real	0m0.238s
user	0m0.347s
sys	0m0.060s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 2

real	0m0.233s
user	0m0.343s
sys	0m0.059s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 2

real	0m0.233s
user	0m0.344s
sys	0m0.058s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 2

real	0m0.236s
user	0m0.350s
sys	0m0.060s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 2

real	0m0.239s
user	0m0.352s
sys	0m0.060s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 2

real	0m0.252s
user	0m0.368s
sys	0m0.065s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 4

real	0m0.201s
user	0m0.414s
sys	0m0.163s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 4

real	0m0.202s
user	0m0.414s
sys	0m0.163s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 4

real	0m0.203s
user	0m0.417s
sys	0m0.164s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 4

real	0m0.199s
user	0m0.411s
sys	0m0.162s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 4

real	0m0.199s
user	0m0.410s
sys	0m0.161s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 4

real	0m0.201s
user	0m0.414s
sys	0m0.163s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 4

real	0m0.202s
user	0m0.416s
sys	0m0.163s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 8

real	0m0.429s
user	0m0.619s
sys	0m1.097s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 8

real	0m0.434s
user	0m0.627s
sys	0m1.108s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 8

real	0m0.431s
user	0m0.620s
sys	0m1.095s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 8

real	0m0.430s
user	0m0.624s
sys	0m1.095s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 8

real	0m0.429s
user	0m0.623s
sys	0m1.093s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 8

real	0m0.429s
user	0m0.626s
sys	0m1.098s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 8

real	0m0.433s
user	0m0.627s
sys	0m1.103s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 8

real	0m0.437s
user	0m0.630s
sys	0m1.097s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 6

real	0m0.320s
user	0m0.536s
sys	0m0.564s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 6

real	0m0.284s
user	0m0.517s
sys	0m0.504s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 6

real	0m0.277s
user	0m0.506s
sys	0m0.491s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 6

real	0m0.315s
user	0m0.552s
sys	0m0.541s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 6

real	0m0.283s
user	0m0.510s
sys	0m0.508s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 6

real	0m0.280s
user	0m0.513s
sys	0m0.492s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 6

real	0m0.272s
user	0m0.491s
sys	0m0.489s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 12

real	0m0.657s
user	0m0.733s
sys	0m2.291s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 12

real	0m0.655s
user	0m0.731s
sys	0m2.270s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 12

real	0m0.657s
user	0m0.733s
sys	0m2.290s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 12

real	0m0.654s
user	0m0.733s
sys	0m2.272s
(base) Grigores-MBP:Lab3 grigorelucian$ time ./oets 10000 12

real	0m0.653s
user	0m0.730s
sys	0m2.269s

*/