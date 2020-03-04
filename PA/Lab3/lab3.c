#include <stdio.h>
#include <stdlib.h>

void problema_rucsacului(float m[], float v[], int len, int max)
{
    float p[len];
    int k;
    // initializare ponderi
    for (k = 0; k < len; k++)
    {
        p[k] = v[k] / m[k];
    }

    // sortare descrescatoare dupa ponderi
    for (k = 0; k < (len - 1); k++)
    {
        int j = k + 1;
        for (; j < len; j++)
        {
            if (p[j] > p[k])
            {
                int temp = p[k];
                p[k] = p[j];
                p[j] = temp;
                temp = v[k];
                v[k] = v[j];
                v[j] = temp;
                temp = m[k];
                m[k] = m[j];
                m[j] = temp;
            }
        }
    }

    // umplere rucsac
    float cant = 0, val = 0;
    while (cant < max)
    {
        for (k = 0; k < len; k++)
        {
            if (cant + m[k] <= max)
            {
                cant += m[k];
                val += v[k];
                printf("Se adauga in totalitate elem cu masa %.2f\n", m[k]);
                if (cant == max)
                {
                    break;
                }
            }
            if (cant + m[k] > max)
            {
                float procent = (max - cant) / m[k];
                cant += m[k] * procent;
                val += v[k] * procent;
                printf("Se adauga in proportie de %.3f elem cu masa %.2f\n", procent, m[k]);
                break;
            }
        }
    }
    printf("Valoare totala rucsac = %.2f\n", val);
}

void problema_spectacolelor(float start[], float final[], int nr_filme)
{
    int k;
    // ordonare crescatoare dupa timpul de terminare al filmelor
    for (k = 0; k < (nr_filme - 1); k++)
    {
        int j = k + 1;
        for (; j < nr_filme; j++)
        {
            if (final[j] < final[k])
            {
                int temp = final[j];
                final[j] = final[k];
                final[k] = temp;
                temp = start[j];
                start[j] = start[k];
                start[k] = temp;
            }
        }
    }
    
    // punere in redare filme
    int final_spectacol = 0, nr = 0;
    for (k = 0; k < nr_filme; k++)
    {
        if (start[k] >= final_spectacol)
        {
            nr++;
            final_spectacol = final[k];
            printf("Se reda filmul de la %.2f la %.2f\n", start[k], final[k]);
        }
    }
    printf("S-au redat in total %d filme\n", nr);
}

void problema_cuburi()
{
}

int main()
{
    // PROBLEMA RUCSACULUI
    float m[] = {10, 30, 20};
    float v[] = {60, 120, 100};
    int nr_obj = 3;
    int max = 50;
    printf("\n--- PROBLEMA RUCSACULUI ---\n");
    problema_rucsacului(m, v, nr_obj, max);

    // PROBLEMA SPECTACOLELOR
    float start[] = {10, 11, 12, 14, 16, 17};
    float final[] = {11, 13, 13, 18, 17, 19};
    int nr_filme = 6;
    printf("\n--- PROBLEMA SPECTACOLELOR ---\n");
    problema_spectacolelor(start, final, nr_filme);

    // PROBLEMA CUBURI

    problema_cuburi();
    return 0;
}