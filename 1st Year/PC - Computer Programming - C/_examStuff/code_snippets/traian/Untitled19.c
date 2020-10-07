#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PUNCTE 10

typedef struct {
    double x;
    double y;    
} TPunct;

void print_punct(TPunct punct) 
{
    printf("(%lf, %lf)\n", punct.x, punct.y);    
}

void print_puncte(TPunct* puncte, int num)
{
    int i;
    printf("Avem %d puncte: \n", num);
    for (i = 0; i < num; i++)
    {
        print_punct(puncte[i]);
    }
} 

int comp1 (const void* elem1, const void* elem2) 
{
    TPunct* punct1 = (TPunct*)elem1;
    TPunct* punct2 = (TPunct*)elem2;
    return punct1->x - punct2->x;
}

int comp2 (const void* elem1, const void* elem2) 
{
    TPunct* punct1 = (TPunct*)elem1;
    TPunct* punct2 = (TPunct*)elem2;
    return punct1->y - punct2->y;
}

int main() 
{
    TPunct puncte[NUM_PUNCTE];
    int i;
    
    srand(time(NULL));
    for (i = 0; i < NUM_PUNCTE; i++)
    {
        puncte[i].x = rand() % 100;
        puncte[i].y = rand() % 100;
    }
    print_puncte(puncte, NUM_PUNCTE);
    
    printf("Ordonez punctele pe axa Ox!\n");
    qsort(puncte, NUM_PUNCTE, sizeof(TPunct), comp1);
    print_puncte(puncte, NUM_PUNCTE);

    printf("Ordonez punctele pe axa Oy!\n");
    qsort(puncte, NUM_PUNCTE, sizeof(TPunct), comp2);
    print_puncte(puncte, NUM_PUNCTE);
    
    getch();
    return 0;
}
