/*
    Grigore Lucian-Florin
    Grupa 336CA
    Algoritmi Paraleli si Distribuiti
    Tema 1
*/
#include <bits/stdc++.h>
using namespace std;
#include "pthread_barrier_mac.h"

char *fjulia_in;
char *fjulia_out;
char *fmandelbrot_in;
char *fmandelbrot_out;
int no_threads;

typedef struct
{
    double a;
    double b;
} TComplex;

typedef struct
{
    // TODO
} TThreadArgs;

void get_args(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("Numar incorect de parametri:\n\t"
               "./tema1 fisier_intrare_julia fisier_iesire_julia "
               "fisier_intrare_mandelbrot fisier_iesire_mandelbrot "
               "[numar thread-uri]\n");
        exit(1);
    }

    fjulia_in = argv[1];
    fjulia_out = argv[2];
    fmandelbrot_in = argv[3];
    fmandelbrot_out = argv[4];
    no_threads = atoi(argv[5]);
}

void *f_thread_julia(void *args)
{
    TThreadArgs *curr_args = (TThreadArgs *)args;
    // TODO create fractal

    // bariera intre creare si exportare
    // TODO export image
    pthread_exit(NULL);
}

void *f_thread_mandelbrot(void *args)
{
    TThreadArgs *curr_args = (TThreadArgs *)args;
    // TODO create fractal

    // bariera intre creare si exportare
    // TODO export image
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int status;
    // citesc argumentele programului
    get_args(argc, argv);

    // creare thread-uri
    pthread_t threads[no_threads];

    // initializare thread-uri
    for (int i = 0; i < no_threads; ++i)
    {
        if (i % 2)
        { // initializare thread folosit pt Julia
            // TODO assign arguments
            TThreadArgs curr_arg;

            status = pthread_create(&threads[i], NULL, f_thread_julia, &curr_arg);

            if (status)
            {
                cout << "Eroare la crearea thread-ului " << i << " pentru Julia\n";
                exit(-1);
            }
        }
        else
        { // initializare thread folosit pt Mandelbrot
            // TODO assign arguments
            TThreadArgs curr_arg;

            status = pthread_create(&threads[i], NULL, f_thread_julia, &curr_arg);

            if (status)
            {
                cout << "Eroare la crearea thread-ului " << i << " pentru Mandelbrot\n";
                exit(-1);
            }
        }
    }

    return 0;
}
