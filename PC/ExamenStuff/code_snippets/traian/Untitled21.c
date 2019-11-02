/* 
sprintf example 
from: http://www.cplusplus.com/reference/cstdio/sprintf/
*/
#include <stdio.h>
#include <conio.h>

int main ()
{
  char buffer [50];
  int n, a=5, b=3;
  n=sprintf (buffer, "%d plus %d is %d", a, b, a+b);
  printf ("[%s] is a string %d chars long\n",buffer,n);
  getch();
  return 0;
}
