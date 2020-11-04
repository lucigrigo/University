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

// structura pentru reprezentarea unui numar complex
typedef struct
{
    double a;
    double b;
} TComplex;

typedef struct
{
    int is_julia;
    double x_min;
    double x_max;
    double y_min;
    double y_max;
    int iterations;
    double resolution;
    TComplex c_julia;
} TInputArgs;

// structura pentru comunicarea argumentelor unui singur thread
typedef struct
{
    // TODO
    TInputArgs fractal_args;
    int thread_id;
} TThreadArgs;

// functie care se ocupa de citirea si
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

void read_input_file(char *filename, TInputArgs *args)
{
    FILE *ffile = fopen(filename, "r");
    if (ffile == NULL)
    {
        cout << "Eroare la deschiderea fisierului de intrare!" << endl;
        ;
        exit(1);
    }

    fscanf(ffile, "%d", &args->is_julia);
    fscanf(ffile, "%lf %lf %lf %lf",
           &args->x_min, &args->x_max, &args->y_min, &args->y_max);
    fscanf(ffile, "%lf", &args->resolution);
    fscanf(ffile, "%d", &args->iterations);

    if (args->is_julia)
    {
        fscanf(ffile, "%lf %lf", &args->c_julia.a, &args->c_julia.b);
    }

    fclose(ffile);
}

void write_output_file(char *filename, int **result, int x_start, int x_end,
                        int y_start, int y_end, int width, int height)
{
    FILE *ffile = fopen(filename, "w");
    if (ffile == NULL)
    {
        cout << "Eroare la deschiderea fisierului de iesire!" << endl;
        exit(1);
    }

    fprintf(ffile, "P2\n%d %d\n255\n", width, height);
    for(int i = x_start; i < x_end; ++i) {
        for(int j = y_start; j < y_end; ++j) {
            fprintf(ffile, "%d ", result[i][j]);
        }
        fprintf(ffile, "\n");
    }

    fclose(ffile);
}

int **alloc_mem(int width, int height) {
    int **x;
    x = (int **) malloc(height * sizeof(int *));
    if(x == NULL) return NULL;
    for(int i = 0; i < height; ++i) {
        x[i] = (int *) malloc(width * sizeof(int));
        if(x[i] == NULL) return NULL;
    }
    return x;
}

void free_mem(int **x, int height) {
    for(int i = 0; i < height; ++i)
        free(x[i]);
    free(x);
}

void *f_thread_julia(void *args)
{
    TThreadArgs *curr_args = (TThreadArgs *)args;
    int x_start;
    int x_end;

    // TODO create fractal

    // bariera intre creare si exportare
    // TODO export fractal to file
    pthread_exit(NULL);
}

void *f_thread_mandelbrot(void *args)
{
    TThreadArgs *curr_args = (TThreadArgs *)args;
    // TODO create fractal

    // bariera intre creare si exportare
    // TODO export fractal to file
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
            // TODO assign arguments to pass
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
            // TODO assign arguments to pass
            TThreadArgs curr_arg;

            status = pthread_create(&threads[i], NULL, f_thread_julia, &curr_arg);

            if (status)
            {
                cout << "Eroare la crearea thread-ului " << i << " pentru Mandelbrot\n";
                exit(-1);
            }
        }
    }

    // asteptarea thread-urilor sa se finalizeze
    for (int i = 0; i < no_threads; i++)
    {
        void *s;
        status = pthread_join(threads[i], &s);

        if (status)
        {
            printf("Eroare la asteptarea thread-ului %d\n", i);
            exit(-1);
        }
    }

    return 0;
}
