// TURNURILE DIN HANOI
#include <stdlib.h>
#include <stdio.h>

void hanoi(int nr, char start_stiva, char final_stiva, char aux_stiva) {
    if(nr == 1) {
        printf("Se muta un disc de pe %c pe %c\n", start_stiva, final_stiva);
        return;
    }
    hanoi(nr - 1, start_stiva, aux_stiva, final_stiva);
    printf("Se muta un disc de pe %c pe %c\n", start_stiva, final_stiva);
    hanoi(nr - 1, aux_stiva, final_stiva, start_stiva);
}

int main() {
    int n = 3;
    hanoi(n, 'A', 'B', 'C');
    printf("-----\n");
    n = 2;
    hanoi(n, 'A', 'B', 'C');
    return 0;
}