#include <stdlib.h>
#include <stdio.h>

void problema_rucsacului_discret(int m[], int v[], int n, int max)
{
    int i;

    for (i = 0; i < (n - 1); i++)
    {
        int j = i + 1;
        for (; j < n; j++)
        {
            if (m[j] > m[i])
            {
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
                temp = m[i];
                m[i] = m[j];
                m[j] = temp;
            }
        }
    }

    int nr_obj = 1;
    int obj[n];
    obj[0] = m[0];
    int index = 1;
    max -= m[0];
    i = 1;

    while (i < n)
    {
        if (obj[i - 1] <= obj[i - 1] + v[i] && max - m[i] >= 0)
        {
            obj[index++] = m[i];
            max -= m[i];
            nr_obj++;
            if (max == 0)
            {
                break;
            }
        }
        i++;
    }

    printf("nr obiecte = %d\n", nr_obj);
    printf("obiectele din rucsac au masele:\n");
    i = 0;
    while (i < nr_obj)
    {
        printf("\t%d\n", obj[i]);
        i++;
    }
}

void problema_subsir(int v[], int n)
{
    int D[n];
    int i;

    for (i = 0; i < n; i++)
    {
        D[i] = 0;
    }

    for (i = 0; i < n; i++)
    {
        int j = 0;
        int max = 0;
        for (; j < i; j++)
        {
            if (D[j] > max && v[i] > v[j])
            {
                max = D[j];
            }
        }
        D[i] = max + 1;
    }

    int max = -1;
    for (i = 0; i < n; i++)
    {
        if (D[i] > max)
        {
            max = D[i];
        }
    }
    printf("lungimea maxima este %d\n", max);
    printf("si vectorul cu lungimi este:\n\t");
    for (i = 0; i < n; i++)
    {
        printf("%d ", D[i]);
    }
    printf("\n");
}

int main()
{
    printf("\n---------------------------------------------\n");

    printf("\n--- PROBLEMA RUCSACULUI DISCRET ---\n");
    int m[] = {10, 30, 20};
    int v[] = {60, 120, 100};
    problema_rucsacului_discret(m, v, 3, 50);

    printf("\n--- PROBLEMA CELUI MAI LUNG SUBSIR ---\n");
    int v1[] = {6, 1, 2, 9, 3, 8, 4, 7};
    problema_subsir(v1, 8);

    printf("\n---------------------------------------------\n");
    return 0;
}