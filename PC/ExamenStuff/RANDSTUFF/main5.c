#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void swap(char *t1, char *t2) {
//   char *t;
//   t = t1;
//   t1 = t2;
//   t2 = t;
// }
// int main() {
//   char *s[2] = {"Hello", "World"};
//   swap(s[0], s[1]);
//   printf("%s\n%s\n", s[0], s[1]);
//   return 0;
// }

typedef struct {
  char a[101];
} TS;

int main() {
  TS A;
  strcpy(A.a, "asdasdadsadsada");
  printf("%s\n", A.a);
  return 0;
}
