#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// REZOLVARE EXERCITIUL 1 -> codul compilat si rulat cu mai multe valori pt NUM_THREADS
// #define NUM_THREADS 4

void *f(void *arg) {
  	long id = (long)arg;
	// REZOLVARE EXERCITIUL 3 -> scrierea de 100 de ori a 'Hello World' pe mai multe thread-uri
	// Observatie: Uneori, mesajele de pe thread-uri diferite sunt intercalate unele cu celelalte
	// 	pentru ca executia acestora este nedeterminista. Nu poate fi aceeasi ordine de executare mereu.
	for(int i = 0; i < 100; ++i)
		printf("scriem \'Hello World\' #%d din thread-ul %ld!\n", i, id);
  	pthread_exit(NULL);
}

// REZOLVARE EXERCITIUL 4 -> functie folosita pentru al doilea thread creeat
void *f2(void *arg) {
	long id = (long)arg;
	for(int i = 0; i < 100; ++i) 
		printf("numaram %d din thread %ld\n", i, id);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	// REZOLVARE EXERCITIUL 2 -> numarul de thread-uri sa corespunda cu cele de sistem
	long cores = sysconf(_SC_NPROCESSORS_CONF);
	pthread_t threads[cores];
  	int r;
  	long id = 0;
  	void *status;

	// COD FOLOSIT PENTRU EXERCITIILE 1 SI 2 si 3
  	// for (id = 0; id < cores; id++) {
	// 	r = pthread_create(&threads[id], NULL, f, (void *)id);

	// 	if (r) {
	//   		printf("Eroare la crearea thread-ului %ld\n", id);
	//   		exit(-1);
	// 	}
  	// }

  	// for (id = 0; id < cores; id++) {
	// 	r = pthread_join(threads[id], &status);

	// 	if (r) {
	//   		printf("Eroare la asteptarea thread-ului %ld\n", id);
	//   		exit(-1);
	// 	}
  	// }

	// COD FOLOSIT PENTRU EXERCITIUL 4
	r = pthread_create(&threads[0], NULL, f, (void *)id++);
	if (r) {
		printf("Eroare la crearea thread-ului 0");
		exit(-1);
	}

	r = pthread_create(&threads[1], NULL, f2, (void *)id);
	if (r) {
		printf("Eroare la crearea thread-ului 1");
		exit(-1);
	}

	r = pthread_join(threads[0], &status);
	if (r) {
		printf("Eroare la join thread 0");
		exit(-1);
	}

	r = pthread_join(threads[1], &status);
	if (r) {
		printf("Eroare la join thread 1");
		exit(-1);
	}

  	pthread_exit(NULL);
}
