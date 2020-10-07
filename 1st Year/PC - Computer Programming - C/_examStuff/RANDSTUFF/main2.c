#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char s[] = "abbacdde";
  int i;
  i = 0;
  while (i < strlen(s) - 1) {
    if (s[i] == s[i + 1]) {
      strcpy(s + i, s + i + 2);
      if (i > 0) {
        i = i - 1;
      }
    } else {
      i = i + 1;
    }
  }
  printf("%s\n", s);
  return 0;
}
