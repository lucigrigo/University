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
int no_threads_julia;
int no_threads_mandelbrot;
int **julia;
int **mandelbrot;
pthread_barrier_t julia_barrier;
pthread_barrier_t mandelbrot_barrier;

// structura pentru reprezentarea unui numar complex
typedef struct
{
    double a;
    double b;
} TComplex;

// structura pentru reprezentarea argumentelor de intrare
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
    TInputArgs fractal_args;
    int thread_id;
    int width;
    int height;
} TThreadArgs;

// functie care se ocupa de citirea argumentelor programului
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

// functie care se ocupa de citirea datelor de intrare dintr-un fisier
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

// functie care scrie rezultatul intr-un fisier de iesire
void write_output_file(char *out_filename, int **result, int width, int height)
{
    int i, j;

    FILE *file = fopen(out_filename, "w");
    if (file == NULL)
    {
        printf("Eroare la deschiderea fisierului de iesire!\n");
        return;
    }

    fprintf(file, "P2\n%d %d\n255\n", width, height);
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            fprintf(file, "%d ", result[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// functie care aloca memorie pentru un fractal
int **alloc_mem(int width, int height)
{
    int **x;
    x = (int **)malloc(height * sizeof(int *));
    if (x == NULL)
        return NULL;
    for (int i = 0; i < height; ++i)
    {
        x[i] = (int *)malloc(width * sizeof(int));
        if (x[i] == NULL)
            return NULL;
    }
    return x;
}

// functie care elibereaza memoria pentru un fractal
void free_mem(int **x, int height)
{
    for (int i = 0; i < height; ++i)
        free(x[i]);
    free(x);
}

// functie care este executata de un thread pentru Julia
void *f_thread_julia(void *args)
{
    TThreadArgs *julia_args = (TThreadArgs *)args;
    int width = julia_args->width;
    int height = julia_args->height / 2;
    int w_start = julia_args->thread_id * (double) width / no_threads_julia;
    int w_end = min((julia_args->thread_id + 1) * (double) width / no_threads_julia, (double) width);
    int h_start = julia_args->thread_id * (double) height / no_threads_julia;
    int h_end = min((julia_args->thread_id + 1) * (double) height / no_threads_julia, (double) height);

    // create fractal
    for (int w = w_start; w < w_end; ++w)
    {
        for (int h = 0; h < julia_args->height; ++h)
        {
            int step = 0;
            TComplex z = {.a = w * julia_args->fractal_args.resolution +
                               julia_args->fractal_args.x_min,
                          .b = h * julia_args->fractal_args.resolution +
                               julia_args->fractal_args.y_min};
            
            while(sqrt(pow(z.a, 2.0) + pow(z.b, 2.0)) < 2.0 &&
            step < julia_args->fractal_args.iterations) {
                TComplex z_aux = {.a = z.a, .b = z.b};

                z.a = pow(z_aux.a, 2) - pow(z_aux.b, 2) +
                julia_args->fractal_args.c_julia.a;
                z.b = 2 * z_aux.a * z_aux.b +
                julia_args->fractal_args.c_julia.b;

                ++step;
            }

            julia[h][w] = step % 256;
        }
    }

    // bariera intre generare si transformare
    pthread_barrier_wait(&julia_barrier);

    // transforma rezultatul din coordonate matematice in coordonate ecran
	for (int i = h_start; i < h_end; i++) {
		int *aux = julia[i];
		julia[i] = julia[julia_args->height - i - 1];
		julia[julia_args->height - i - 1] = aux;
	}

    pthread_exit(NULL);
}

// functie care este executata de un thread pentru Mandelbrot
void *f_thread_mandelbrot(void *args)
{
    TThreadArgs *curr_args = (TThreadArgs *)args;
    // TODO create fractal

    // bariera intre creare si transformare
    // TODO export fractal to file
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int status;
    // citire argumente program
    get_args(argc, argv);

    // citire fisier intrare Julia
    TInputArgs julia_args;
    read_input_file(fjulia_in, &julia_args);

    // citire fisier intrare Mandelbrot
    TInputArgs mandelbrot_args;
    read_input_file(fmandelbrot_in, &mandelbrot_args);

    // calcul inaltimi si latimi
    int julia_width = (julia_args.x_max - julia_args.x_min) / julia_args.resolution;
    int julia_height = (julia_args.y_max - julia_args.y_min) / julia_args.resolution;
    int mandelbrot_width = (mandelbrot_args.x_max - mandelbrot_args.x_min) / mandelbrot_args.resolution;
    int mandelbrot_height = (mandelbrot_args.y_max - mandelbrot_args.y_min) / mandelbrot_args.resolution;

    // alocarea memorie pentru rezultate
    julia = alloc_mem(julia_width, julia_height);
    mandelbrot = alloc_mem(mandelbrot_width, mandelbrot_height);
    if (julia == NULL || mandelbrot == NULL)
    {
        printf("eroare la alocarea memoriei\n");
        exit(-1);
    }

    // initializare bariere pentru cei doi fractali
    no_threads_julia = (no_threads % 2 == 1) ? no_threads / 2 + 1 : no_threads / 2;
    no_threads_mandelbrot = no_threads / 2;
    pthread_barrier_init(&julia_barrier, NULL, no_threads_julia);
    pthread_barrier_init(&mandelbrot_barrier, NULL, no_threads_mandelbrot);

    // creare thread-uri
    pthread_t threads[no_threads];

    // initializare thread-uri
    for (int i = 0; i < no_threads; ++i)
    {
        if (i % 2)
        {
            // initializare thread folosit pentru Julia
            TThreadArgs curr_arg;
            memcpy(&curr_arg, &julia_args, sizeof(TInputArgs));
            curr_arg.thread_id = i / 2;
            curr_arg.width = julia_width;
            curr_arg.height = julia_height;

            status = pthread_create(&threads[i], NULL, f_thread_julia, &curr_arg);

            if (status)
            {
                cout << "Eroare la crearea thread-ului " << i << " pentru Julia\n";
                exit(-1);
            }
        }
        else
        {
            // initializare thread folosit pentru Mandelbrot
            TThreadArgs curr_arg;
            memcpy(&curr_arg, &mandelbrot_args, sizeof(TInputArgs));
            curr_arg.thread_id = i / 2;
            curr_arg.width = julia_width;
            curr_arg.height = julia_height;

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

    // scriere rezultate in fisierul de iesire
    write_output_file(fjulia_out, julia, julia_width, julia_height);
    write_output_file(fmandelbrot_out, mandelbrot, mandelbrot_width, mandelbrot_height);

    // eliberare memorie alocata
    free_mem(julia, julia_height);
    free_mem(mandelbrot, mandelbrot_height);

    return 0;
}
