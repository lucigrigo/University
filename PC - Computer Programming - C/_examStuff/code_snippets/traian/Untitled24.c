#include <stdio.h>
#include <conio.h>

typedef struct {
    double x, y;
    char active;
    char name[24];
} TPunct;

void fwrite_punct(TPunct* p, FILE* f)
{
    fwrite(&(p->x), sizeof(p->x), 1, f);
    fwrite(&(p->y), sizeof(p->y), 1, f);
    fwrite(&(p->active), sizeof(p->active), 1, f);
    fwrite(&(p->name), sizeof(p->name), 1, f);
}

int main() 
{
    TPunct p = {3, 2, 1, "alea iacta est"};
    FILE* f = fopen("myfile3.bin", "w");
    FILE* f1 = fopen("myfile4.bin", "w");
    printf("%d", sizeof(TPunct));
    
    if (f)
    {
        fwrite_punct(&p, f);
        fclose(f);
    }
    if (f1)
    {
        fwrite(&p, sizeof(p), 1, f1);
        fclose(f1);
    }
    
    return 1;
}
