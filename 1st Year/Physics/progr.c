#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Dati nr de masuratori:\n");
  int nr;
  scanf("%d", &nr);
  int i = 0;
  double C_2 = (0.01438);
  double logn = (log(0.40));
  double lambda = ((0.655) * pow(10, -6));
  while (i < nr) {
    double TS;
    printf("Temperatura de stralucire?\n");
    scanf("%lf", &TS);
    double T = ((C_2 * TS) / (lambda * TS * logn + C_2));
    printf("Temperatura corpului este %lf.\n", T);
    i++;
  }
  return 0;
}
