#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

int a = 0;
// declarare mutex
pthread_mutex_t mutex;

void *f(void *arg)
{
	// blocare mutex
	int status = pthread_mutex_lock(&mutex);
	if(status != 0)
		exit(-1);

	// incrementare
	a += 2;

	// deblocare mutex
	status = pthread_mutex_unlock(&mutex);
	if(status != 0)
		exit(-1);

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int i, r;
	void *status;
	pthread_t threads[NUM_THREADS];
	int arguments[NUM_THREADS];

	// initializare mutex
	r = pthread_mutex_init(&mutex, NULL);
	if(r != 0)
		exit(-1);

	for (i = 0; i < NUM_THREADS; i++) {
		arguments[i] = i;
		r = pthread_create(&threads[i], NULL, f, &arguments[i]);

		if (r) {
			printf("Eroare la crearea thread-ului %d\n", i);
			exit(-1);
		}
	}

	for (i = 0; i < NUM_THREADS; i++) {
		r = pthread_join(threads[i], &status);

		if (r) {
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
	}

	// stergere mutex
	r = pthread_mutex_destroy(&mutex);
	if(r != 0)
		exit(-1);

	printf("a = %d\n", a);

	return 0;
}
