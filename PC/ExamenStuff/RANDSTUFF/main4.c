#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10

void foo(int *x, void *y) {
  printf("%d ", (char *)x - (char *)y);
  ++x;
}

int main(void) {
  int i, *p;
  p = calloc(10, sizeof(int));
  void *p1 = p;
  for (i = 0; i < N; i++, p++) {
    foo(p, p1);
  }
  return 0;
}
