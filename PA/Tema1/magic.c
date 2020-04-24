#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_FILENAME "magic.in"
#define OUTPUT_FILENAME "magic.out"
#define INTEGER_MAX 2147483647
#define min(a, b) ((a) < (b) ? (a) : (b))

struct numar
{
    int index_initial;
    int suma;
};

struct rezultat
{
    int nr_magic;
    int stg;
    int drp;
};

struct numar *numar_nou(int s, int i)
{
    struct numar *n = (struct numar *)malloc(sizeof(struct numar));
    n->index_initial = i;
    n->suma = s;
    return n;
}

int ncomp(const void *p, const void *q)
{
    return (*(struct numar **)p)->suma - (*(struct numar **)q)->suma;
}

struct rezultat *calc_min(struct numar **vect, int start, int final)
{
    // TODO recursively compute minimum
    // compute when 3 elements or less
    // at recombine step take care of all parameters
    return NULL;
}

int main()
{
    // valori de intrare
    int nr_biletele;

    // valori de iesire
    short nr_magic;
    short stanga;
    short dreapta;
    int i;

    // citire date de intrare
    FILE *file_in = fopen(INPUT_FILENAME, "r");
    fscanf(file_in, "%d\n", &nr_biletele);
    struct numar **numere = (struct numar **)malloc(nr_biletele * sizeof(struct numar *));
    int suma = 0;
    for (i = 0; i < nr_biletele; ++i)
    {
        int nr_curent;
        fscanf(file_in, "%d ", &nr_curent);
        numere[i] = numar_nou(suma, i + 1);
        suma += nr_curent;
    }
    fclose(file_in);

    // sortarea punctelor crescator dupa suma
    qsort(numere, nr_biletele, sizeof(struct numar *), ncomp);

    // printf("\nDupa sortare\n");
    // for (i = 0; i < nr_biletele; ++i)
    // {
    //     printf("%d: init=%d s=%d\n", i, numere[i]->index_initial, numere[i]->suma);
    // }

    // calcularea recursiva a minimului
    struct rezultat *rezultat_final = (struct rezultat *)malloc(sizeof(struct rezultat));
    rezultat_final->drp = nr_biletele;
    rezultat_final->stg = 0;
    rezultat_final->nr_magic = 0;
    // rezultat_final = calc_min(numere, 0, nr_biletele);

    // scriere date de iesire
    FILE *file_out = fopen(OUTPUT_FILENAME, "w");
    fprintf(file_out, "%d\n%d %d\n", rezultat_final->nr_magic, rezultat_final->stg, rezultat_final->drp);
    fclose(file_out);
    return 0;
}