/*
    Grigore Lucian-Florin
    Algoritmi Paraleli si Distribuiti
    Test practic 1
*/
#include <bits/stdc++.h>
#include "pthread_barrier_mac.h"
#define ll long long

// macro-uri pentru testare
#define NO_THREADS 8
#define NO_ELEMS 100000
#define ID_EXCEPT 0

ll seq_sum;                // aici salvez suma calculata secvential
ll par_sum;                // doar thread-ul cu ID_EXCEPT are voie sa acceseze aceasta variabila
pthread_barrier_t barrier; // bariera folosita in rezolvare
int v[NO_ELEMS];           // vectorul de elemente

// Structura folosita
typedef struct
{
    int thread_id;
    int *sum;
} TArg;

void *thread_function(void *arg)
{
    TArg args = *(TArg *)arg;
    int start_index = args.thread_id * NO_ELEMS / NO_THREADS;
    int end_index = min(NO_ELEMS, (args.thread_id + 1) * NO_ELEMS / NO_THREADS);

    int loc_sum = 0;
    for (int i = start_index; i < end_index; ++i)
    {
        loc_sum += v[i];
    }
    args.sum[args.thread_id] = loc_sum;

    pthread_barrier_wait(&barrier);
    if (args.thread_id == ID_EXCEPT)
    {
        for (int i = 0; i < NO_THREADS; ++i)
            par_sum += args.sum[i];

        cout << "Parallel sum = " << par_sum << endl;
        // verificare rezultat
        if (seq_sum != par_sum)
        {
            cout << "[WRONG] Sums differ" << endl;
            cout << "\t" << par_sum << " != " << seq_sum << endl;
        }
        else
        {
            cout << "[CORRECT] Sums are equal" << endl;
        }
    }

    pthread_barrier_wait(&barrier);
    free(arg);
    pthread_exit(NULL);
}

int main()
{
    int status;

    // initializare bariera
    pthread_barrier_init(&barrier, NULL, NO_THREADS);

    // initializare sume partiale
    int *sum = (int *)malloc(NO_THREADS * sizeof(int));
    for (int i = 0; i < NO_THREADS; ++i)
        sum[i] = 0;

    // initializare valori in vector
    for (int i = 0; i < NO_ELEMS; ++i)
    {
        v[i] = i + 5;
    }

    // computing sequential sum
    for (int i = 0; i < NO_ELEMS; ++i)
    {
        seq_sum += v[i];
    }
    cout << "Sequential sum = " << seq_sum << endl;

    // initializare thread-uri
    pthread_t threads[NO_THREADS];

    for (int i = 0; i < NO_THREADS; ++i)
    {
        TArg *arg = (TArg *)malloc(sizeof(TArg));
        arg->sum = sum;
        arg->thread_id = i;
        status = pthread_create(&threads[i], NULL, thread_function, arg);

        if (status)
        {
            cout << "Error creating thread " << i << endl;
            exit(-1);
        }
    }

    // asteptare thread-uri
    for (int i = 0; i < NO_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);

        if (status)
        {
            cout << "Error joining thread " << i << endl;
            exit(-1);
        }
    }

    // dezalocare memorie
    pthread_barrier_destroy(&barrier);
    free(sum);
    return 0;
}