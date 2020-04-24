#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define INPUT_FILENAME "teme.in"
#define OUTPUT_FILENAME "teme.out"

struct tema
{
    short punctaj;
    short timp_rezolvare;
    short deadline;
    short index;
    int rezolvata;
};

struct tema *tema_noua(short p, short tr, short d, short i)
{
    struct tema *t = (struct tema *)malloc(sizeof(struct tema));
    t->deadline = d;
    t->punctaj = p;
    t->index = i;
    t->timp_rezolvare = tr;
    t->rezolvata = 0;
    return t;
}

int tcomp(const void *p, const void *q)
{
    struct tema *t1 = *(struct tema **)p;
    struct tema *t2 = *(struct tema **)q;
    if (t1->deadline != t2->deadline)
    {
        return t1->deadline - t2->deadline;
    }
    if (t1->punctaj != t2->punctaj)
    {
        return t2->punctaj - t1->punctaj;
    }
    return t1->index - t2->index;
}

int main()
{
    // valoare de input
    short nr_teme_total;
    short final_deadline;

    // valori de output
    int i;

    // citire date de intrare
    FILE *file_in = fopen(INPUT_FILENAME, "r");
    fscanf(file_in, "%hi\n", &nr_teme_total);
    struct tema **teme = (struct tema **)malloc(nr_teme_total * sizeof(struct tema *));
    for (i = 0; i < nr_teme_total; ++i)
    {
        short timp_rezolvare;
        short punctaj;
        short deadline;
        fscanf(file_in, "%hi %hi %hi\n", &timp_rezolvare, &punctaj, &deadline);
        teme[i] = tema_noua(punctaj, timp_rezolvare, deadline, i + 1);
        final_deadline = max(final_deadline, deadline);
    }
    fclose(file_in);
    // final_deadline--;

    // sortarea temelor
    qsort(teme, nr_teme_total, sizeof(struct tema *), tcomp);

    for (i = 0; i < nr_teme_total; ++i)
    {
        printf("%d - #%d t:%d d:%d p:%d\n", i, teme[i]->index, teme[i]->timp_rezolvare, teme[i]->deadline, teme[i]->punctaj);
    }
    printf("\n\n");

    // alegerea temelor ce trebuie rezolvate
    int sapt_curenta = 0;
    int teme_rezolvate = 0;
    int punctaj_acumulat = 0;
    i = 0;
    while (sapt_curenta < final_deadline)
    {
        if (i >= nr_teme_total || teme[i] == NULL)
            break;
        struct tema *tema_curenta = teme[i];
        // printf("- curent #%d, ddl=%d\n", tema_curenta->index, sapt_curenta);
        if (tema_curenta->deadline <= sapt_curenta)
        {
            i++;
            continue;
        }
        if (sapt_curenta + tema_curenta->timp_rezolvare <= tema_curenta->deadline && tema_curenta->rezolvata != 1)
        {
            int j = i + 1;
            printf("%d\n", i);
            int max_gasit = tema_curenta->punctaj;
            int index_max = -1;
            while (j < nr_teme_total && tema_curenta->deadline + teme[j]->timp_rezolvare >= teme[j]->deadline)
            {
                if (teme[j]->punctaj > max_gasit)
                {
                    index_max = j;
                    max_gasit = teme[j]->punctaj;
                }
                j++;
            }
            printf("\n\tmax=%d index=%d\n", max_gasit, index_max);
            if (index_max != -1)
            {
                if (tema_curenta->timp_rezolvare + teme[index_max]->timp_rezolvare + sapt_curenta <= teme[index_max]->deadline && sapt_curenta + tema_curenta->timp_rezolvare <= tema_curenta->deadline && teme[index_max]->deadline - tema_curenta->deadline <= teme[index_max]->timp_rezolvare)
                {
                    sapt_curenta += tema_curenta->timp_rezolvare + teme[index_max]->timp_rezolvare;
                    punctaj_acumulat += tema_curenta->punctaj;
                    punctaj_acumulat += teme[index_max]->punctaj;
                    tema_curenta->rezolvata = 1;
                    teme[index_max]->rezolvata = 1;
                    i = index_max;
                    printf("\tamandoua\n");
                }
                else if (tema_curenta->punctaj > teme[j]->punctaj)
                {
                    tema_curenta->rezolvata = 1;
                    punctaj_acumulat += tema_curenta->punctaj;
                    sapt_curenta += tema_curenta->timp_rezolvare;
                    printf("\t%d\n", i);
                }
                else
                {
                    teme[index_max]->rezolvata = 1;
                    punctaj_acumulat += teme[index_max]->punctaj;
                    sapt_curenta += teme[index_max]->timp_rezolvare;
                    i = index_max;
                    printf("\t%d\n", index_max);
                }
            }
            else
            {
                tema_curenta->rezolvata = 1;
                punctaj_acumulat += tema_curenta->punctaj;
                sapt_curenta += tema_curenta->timp_rezolvare;
            }
            printf("%d\n", i);
            i++;
        }
        else
        {
            ++i;
        }
    }

    // scriere date de iesire
    FILE *file_out = fopen(OUTPUT_FILENAME, "w");
    printf("\n -- REZULTATE FINALE\n");
    fprintf(file_out, "%d %d\n", punctaj_acumulat, teme_rezolvate);
    printf("%d %d\n", punctaj_acumulat, teme_rezolvate);
    for (i = 0; i < nr_teme_total; ++i)
    {
        if (teme[i]->rezolvata == 1)
        {
            fprintf(file_out, "%hi ", teme[i]->index);
            printf("%hi ", teme[i]->index);
        }
    }
    fclose(file_out);
    return 0;
}