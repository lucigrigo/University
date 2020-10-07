#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double f(int nr, ...) {

  double V[nr], max = 0;
  int i;
  va_list list;
  va_start(list, nr);
  for (i = 0; i < nr; i++) {
    V[i] = pow((double)va_arg(list, int), va_arg(list, double));
  }

  for (i = 0; i < nr; i++) {
    if (V[i] > max) {
      max = V[i];
    }
  }
  va_end(list);
  return max;
}

int main(int argc, char *argv[]) {

  int i = 1, nr;
  char *inputFile, *outputFile;
  while (i < argc) {
    if (strcmp(argv[i], "-input") == 0) {
      inputFile = argv[i + 1];
    } else if (strcmp(argv[i], "-output") == 0) {
      outputFile = argv[i + 1];
    } else if (strcmp(argv[i], "-nr") == 0) {
      nr = atoi(argv[i + 1]);
    }
    i += 2;
  }

#ifdef DEBUG
  printf("%s\n", "AM AJUNS AICI");
#endif

  FILE *ffile = fopen(inputFile, "r");
  int A[nr];
  for (i = 0; i < nr; i++) {
    fscanf(ffile, "%d", &A[i]);
  }
  fclose(ffile);
  ffile = fopen(outputFile, "w");
  for (i = 0; i < nr; i++) {
    fprintf(ffile, "%d\n", A[i]);
  }
  fclose(ffile);

  printf("%f\n", f(2, 3, 1.000, 5, 2.000));
  printf("%f\n", f(3, 3, 1.000, 5, 2.1, 3, 4.00));
  return 0;
}
