#include <stdio.h>
#include <stdlib.h>

int main()
{
    int* p;
    
    int stop = 0;
    while (!stop)
    {
        p = (int*) calloc(10000, sizeof(int));
        //p = (int*) malloc(10000 * sizeof(int));
        if (p){
            //if (p[10] != 0){
//                printf("Am alocat memorie pentru p! Adresa este %p. Elementul al 10-lea este %d\n", p, p[10]);
            //}
        }else{
            printf("Nu mai pot aloca memorie pentru p!\n");
            stop = 1;
        }
        
        free(p);
        printf("Am dezalocat memoria pentru p! Adresa este %p. Elementul al 10-lea este %d\n", p, p[10]);
    }
    
    getch();
    return 1;
}
