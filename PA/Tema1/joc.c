#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define INPUT_FILENAME "joc.in"
#define OUTPUT_FILENAME "joc.out"
#define MAX_NNUM 200

int check_solution(int sol[], short v[], int n, int d_value, int m_value, int n_subs, int n_elem)
{
    int i;
    int n_current_subs = 0;
    int n_current_odd = 0;
    int n_current_elem = 0;
    int is_sub = 0;

    for (i = 0; i < n; ++i)
    {
        if (sol[i] == d_value)
        {
            return 1;
        }
        if (sol[i] == m_value)
        {
            n_current_elem++;
            if (is_sub == 0)
            {
                n_current_subs++;
                is_sub = 1;
            }
            if (v[i] % 2 == 1)
            {
                n_current_odd++;
            }
        }
        else if (is_sub == 1 && sol[i] == 0)
        {
            is_sub = 0;
        }
    }

    if ((n_current_elem != n_elem) || (n_current_odd % 2 != 1) || (n_current_subs != n_subs))
    {
        return 0;
    }
    return 1;
}

int calc_sum(int sol[], short v[], int n, int m_value)
{
    int sum = 0;
    int i;
    for (i = 0; i < n; ++i)
    {
        if (sol[i] == m_value)
        {
            sum += v[i];
        }
    }
    return sum;
}

int main()
{
    // date de intrare
    short n;
    short k;
    short l;
    short numere[MAX_NNUM];

    // date de iesire
    int suma_maxima = -1;

    // variabile folosite in rezolvare
    int sol[MAX_NNUM];
    int val_init = -1;
    int val_max = 1;
    int increment = 1;
    int i;

    // citire date de intrare
    FILE *file_in = fopen(INPUT_FILENAME, "r");
    fscanf(file_in, "%hi %hi %hi\n", &n, &k, &l);
    for (i = 0; i < n; ++i)
    {
        fscanf(file_in, "%hi ", &numere[i]);
    }
    fclose(file_in);

    // initializare vector solutie
    for (i = 0; i < n; ++i)
    {
        sol[i] = val_init;
    }

    // generarea solutiilor
    i = 0;
    while (i >= 0)
    {
        int valid = 0;
        while (!valid && sol[i] <= val_max)
        {
            sol[i] += increment;
            valid = check_solution(sol, numere, n, val_init, val_max, k, l);
        }
        if (sol[i] <= val_max)
        {
            if (i == (n - 1))
            {
                suma_maxima = max(suma_maxima, calc_sum(sol, numere, n, val_max));
            }
            else
            {
                i += 1;
            }
        }
        else
        {
            sol[i] = val_init;
            i -= 1;
        }
    }

    // scriere date de iesire
    FILE *file_out = fopen(OUTPUT_FILENAME, "w");
    fprintf(file_out, "%d", suma_maxima);
    // fprintf(file_out, "asdd");
    fclose(file_out);

    return 0;
}