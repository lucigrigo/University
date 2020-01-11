#include <stdio.h>
#include <stdlib.h>

int main()
{
  int x = 1;

  char *y = (char*)&x;

  printf("%c\n",*y+48);
}
