/*
    Grigore Lucian-Florin
    Grupa 336CA
    Algoritmi Paraleli si Distribuiti
    Tema 1
*/
#include <math.h>
#include <stdio.h>

#include <iostream>
// #include <pthread.h>
#include "pthread_barrier_mac.h"

using namespace std;

#define min(a, b) ((a) < (b) ? (a) : (b))

// variabile folosite pentru citire/scriere
char* fjulia_in;
char* fjulia_out;
char* fmandelbrot_in;
char* fmandelbrot_out;
int no_threads;             // numarul de thread-uri
pthread_barrier_t barrier;  // bariera folosita in rezolvare
int** julia;                // variabila in care va fi memorat fractalul Julia
int** mandelbrot;  // variabila in care va fi memorat fractalul Mandelbrot

// structura pentru reprezentarea unui numar complex
typedef struct {
  double a;
  double b;
} TComplex;

// structura pentru reprezentarea argumentelor de intrare
typedef struct {
  int is_julia;
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  int iterations;
  double resolution;
  int width;
  int height;
  TComplex c_julia;
} TInputArgs;

TInputArgs* julia_args;       // arg de intrare pt Julia
TInputArgs* mandelbrot_args;  // arg de intrare pt Mandelbrot

// functie care se ocupa de citirea argumentelor programului
void get_args(int argc, char* argv[]) {
  if (argc != 6) {
    printf(
        "Numar incorect de parametri:\n\t"
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
void read_input_file(char* filename, TInputArgs* args) {
  FILE* ffile = fopen(filename, "r");
  if (ffile == NULL) {
    cout << "Eroare la deschiderea fisierului de intrare!" << endl;
    exit(1);
  }

  fscanf(ffile, "%d", &args->is_julia);
  fscanf(ffile, "%lf %lf %lf %lf", &args->x_min, &args->x_max, &args->y_min,
         &args->y_max);
  fscanf(ffile, "%lf", &args->resolution);
  fscanf(ffile, "%d", &args->iterations);

  if (args->is_julia) {
    fscanf(ffile, "%lf %lf", &args->c_julia.a, &args->c_julia.b);
  }

  fclose(ffile);
}

// functie care scrie rezultatul intr-un fisier de iesire
void write_output_file(char* out_filename, int** result, int width,
                       int height) {
  int i, j;

  FILE* file = fopen(out_filename, "w");
  if (file == NULL) {
    printf("Eroare la deschiderea fisierului de iesire!\n");
    return;
  }

  fprintf(file, "P2\n%d %d\n255\n", width, height);
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      fprintf(file, "%d ", result[i][j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);
}

// functie care aloca memorie pentru un fractal
int** alloc_mem(int width, int height) {
  int** x;
  x = (int**)malloc(height * sizeof(int*));
  if (x == NULL) return NULL;
  for (int i = 0; i < height; ++i) {
    x[i] = (int*)malloc(width * sizeof(int));
    if (x[i] == NULL) return NULL;
  }
  return x;
}

// functie care elibereaza memoria pentru un fractal
void free_mem(int** x, int height) {
  for (int i = 0; i < height; ++i) free(x[i]);
  free(x);
}

// functia executata de fiecare thread pornit
void* f_thread(void* args) {
  int thread_id = *(int*)args;

  // citire date de intrare Julia pe primul thread
  if (thread_id == 0) {
    julia_args = (TInputArgs*)malloc(sizeof(TInputArgs));
    read_input_file(fjulia_in, julia_args);

    // calcul inaltime si latime
    int width =
        (julia_args->x_max - julia_args->x_min) / julia_args->resolution;
    int height =
        (julia_args->y_max - julia_args->y_min) / julia_args->resolution;
    julia_args->width = width;
    julia_args->height = height;

    // alocare memorie
    julia = alloc_mem(width, height);
  }

  // asteptare bariera
  pthread_barrier_wait(&barrier);

  // Julia
  {
    // variabile folosite pentru paralelizare
    int width = julia_args->width;
    int height = julia_args->height / 2;
    int w_start = thread_id * (double)width / no_threads;
    int w_end = min((thread_id + 1) * (double)width / no_threads, width);
    int h_start = thread_id * (double)height / no_threads;
    int h_end = min((thread_id + 1) * (double)height / no_threads, height);

    // calcul Julia
    for (int w = w_start; w < w_end; ++w) {
      for (int h = 0; h < julia_args->height; ++h) {
        int step = 0;
        TComplex z = {.a = w * julia_args->resolution + julia_args->x_min,
                      .b = h * julia_args->resolution + julia_args->y_min};

        while (sqrt(pow(z.a, 2.0) + pow(z.b, 2.0)) < 2.0 &&
               step < julia_args->iterations) {
          TComplex z_aux = {.a = z.a, .b = z.b};

          z.a = pow(z_aux.a, 2) - pow(z_aux.b, 2) + julia_args->c_julia.a;
          z.b = 2 * z_aux.a * z_aux.b + julia_args->c_julia.b;

          ++step;
        }

        julia[h][w] = step % 256;
      }
    }

    // asteptare bariera
    pthread_barrier_wait(&barrier);

    // transformare Julia
    for (int i = h_start; i < h_end; i++) {
      int* aux = julia[i];
      julia[i] = julia[julia_args->height - i - 1];
      julia[julia_args->height - i - 1] = aux;
    }
  }

  // asteptare bariera
  pthread_barrier_wait(&barrier);

  // scriere rezultat Julia
  if (thread_id == 0) {
    write_output_file(fjulia_out, julia, julia_args->width, julia_args->height);
    free_mem(julia, julia_args->height);
    free(julia_args);
  }

  // asteptare bariera
  pthread_barrier_wait(&barrier);

  // citire fisier de intrare Mandelbrot pe primul thread
  if (thread_id == 0) {
    mandelbrot_args = (TInputArgs*)malloc(sizeof(TInputArgs*));
    read_input_file(fmandelbrot_in, mandelbrot_args);

    // calcul inaltime si latime
    int width = (mandelbrot_args->x_max - mandelbrot_args->x_min) /
                mandelbrot_args->resolution;
    int height = (mandelbrot_args->y_max - mandelbrot_args->y_min) /
                 mandelbrot_args->resolution;
    mandelbrot_args->width = width;
    mandelbrot_args->height = height;

    // alocare memorie
    mandelbrot = alloc_mem(width, height);
  }

  // asteptare bariera
  pthread_barrier_wait(&barrier);

  // Mandelbrot
  {
    // variabile folosite in paralelizare
    int width = mandelbrot_args->width;
    int height = mandelbrot_args->height / 2;
    int w_start = thread_id * (double)width / no_threads;
    int w_end = min((thread_id + 1) * (double)width / no_threads, width);
    int h_start = thread_id * (double)height / no_threads;
    int h_end = min((thread_id + 1) * (double)height / no_threads, height);

    // calcul Mandelbrot
    for (int w = w_start; w < w_end; ++w) {
      for (int h = 0; h < mandelbrot_args->height; ++h) {
        TComplex c = {
            .a = w * mandelbrot_args->resolution + mandelbrot_args->x_min,
            .b = h * mandelbrot_args->resolution + mandelbrot_args->y_min};
        TComplex z = {.a = 0, .b = 0};
        int step = 0;

        while (sqrt(pow(z.a, 2.0) + pow(z.b, 2.0)) < 2.0 &&
               step < mandelbrot_args->iterations) {
          TComplex z_aux = {.a = z.a, .b = z.b};

          z.a = pow(z_aux.a, 2.0) - pow(z_aux.b, 2.0) + c.a;
          z.b = 2.0 * z_aux.a * z_aux.b + c.b;

          ++step;
        }

        mandelbrot[h][w] = step % 256;
      }
    }

    // asteptare bariera
    pthread_barrier_wait(&barrier);

    // transformare Mandelbrot
    for (int i = h_start; i < h_end; i++) {
      int* aux = mandelbrot[i];
      mandelbrot[i] = mandelbrot[mandelbrot_args->height - i - 1];
      mandelbrot[mandelbrot_args->height - i - 1] = aux;
    }
  }
  // asteptare bariera
  pthread_barrier_wait(&barrier);

  // scriere date de iesire Mandelbrot
  if (thread_id == 0) {
    write_output_file(fmandelbrot_out, mandelbrot, mandelbrot_args->width,
                      mandelbrot_args->height);
    free_mem(mandelbrot, mandelbrot_args->height);
    free(mandelbrot_args);
  }

  // termina thread
  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  int status;
  // citire argumente program
  get_args(argc, argv);

  // initializare bariera
  pthread_barrier_init(&barrier, NULL, no_threads);

  // creare thread-uri
  pthread_t threads[no_threads];
  int thread_ids[no_threads];

  // initializare thread-uri
  for (int i = 0; i < no_threads; ++i) {
    thread_ids[i] = i;

    status = pthread_create(&threads[i], NULL, f_thread, &thread_ids[i]);

    if (status) {
      printf("Eroare la crearea thread-ului %d\n", i);
      exit(-1);
    }
  }

  // asteptarea thread-urilor sa se finalizeze
  for (int i = 0; i < no_threads; i++) {
    void* s;
    status = pthread_join(threads[i], &s);

    if (status) {
      printf("Eroare la asteptarea thread-ului %d\n", i);
      exit(-1);
    }
  }

  // dezalocarea barierei
  pthread_barrier_destroy(&barrier);

  return 0;
}
