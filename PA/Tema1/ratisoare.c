#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILENAME "ratisoare.in"
#define OUTPUT_FILENAME "ratisoare.out"

struct rata
{
    int linie;
    int coloana;
    int index_initial;
    char *orientare;
    int timp;
};

struct rata *rata_noua(int l, int c, int i, char *o)
{
    struct rata *r = (struct rata *)malloc(sizeof(struct rata));
    r->orientare = (char *)malloc(2 * sizeof(char));
    strcpy(r->orientare, o);
    r->index_initial = i;
    r->linie = l;
    r->coloana = c;
    return r;
}

struct rata** calc_timp(){
    // TODO
    return NULL;
}

int init_comp(const void *p, const void *q)
{
    // TODO
    // sort rate dupa linie si coloana crescator
    return 0;
}

int final_comp(const void *p, const void *q){
    // TODO 
    // sort rate dupa timpul de iesire
    return 0;
}

int main()
{
    // valori de input
    short nr_linii;
    short nr_coloane;
    int k;
    int nr_ratisoare;

    // valoare de iesire
    int index_k;
    int i;

    // citire date de intrare
    FILE *file_in = fopen(INPUT_FILENAME, "r");
    fscanf(file_in, "%hi %hi %d %d\n", &nr_linii, &nr_coloane, &k, &nr_ratisoare);
    struct rata **rate = (struct rata **)malloc(nr_ratisoare * sizeof(struct rata *));
    for (i = 0; i < nr_ratisoare; ++i)
    {
        int identificator;
        int index_linie;
        int index_coloana;
        char *orientare;
        fscanf(file_in, "%d %d %d %c\n", &identificator, &index_linie, &index_coloana, orientare);
        rate[i] = rata_noua(index_linie, index_coloana, i, orientare);
    }
    fclose(file_in);

    // scriere date de iesire
    FILE *file_out = fopen(OUTPUT_FILENAME, "w");
    fprintf(file_out, "%d", index_k);
    fclose(file_out);
    return 0;
}