#include <stdio.h>
#include <stdlib.h>

typedef int (*funcptr_t)(int);
int myfoo(int i) {
  printf("%d\n", i + 1);
  return i;
}
funcptr_t foo(int i) {
  printf("%d\n", i + 1);
  return myfoo;
}
int main() {
  funcptr_t fooptr = foo(0);
  fooptr(10);
  printf("%p %p\n", fooptr, myfoo);
  return 0;
}
