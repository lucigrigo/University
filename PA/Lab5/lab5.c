#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// functie care interschimba 2 valori
int schimba(char *x, char *y)
{
    if (strcmp(x, y) == 0)
    {
        return 1;
    }
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
    return 0;
}

// functie care foloseste backtracking pentru afisarea unei permutari
void permutare(char *a, int l, int n)
{
    if (l == n)
    {
        printf("\t%s\n", a);
        return;
    }
    int i;
    for (i = 0; i < n; i++)
    {
        if (schimba((a + l), (a + i)) == 1)
        {
            continue;
        }
        permutare(a, l + 1, n);
        schimba((a + l), (a + i));
    }
}

// functie care printeaza toate solutiile de aranjare a scandurilor
// pentru lungimea de la un moment dat
void printare_solutie_garduri(int k, int L)
{
    int j;
    char *a = (char *)malloc(L * sizeof(char));
    for (j = 0; j < L; j++)
    {
        // a[j] = '|';
        strcpy((a + j), "|");
    }
    //printf("\t%s\n", a);
    permutare(a, 0, L - 1);
}

void k_garduri(int n, int k)
{
    // initializare vector care memoreaza nr de solutii
    int D[n];

    // cazurile de baza
    D[1] = 1;
    D[2] = 2;

    // desfasurarea recurentei pt nr de solutii
    int i = 3;
    for (; i <= n; i++)
    {
        // nr de solutii pentru gardul de lungime i
        D[i] = D[i - 1] + D[i - k];
    }

    // printare rezultat
    printf("Solutii obtinute:\n");
    for (i = 1; i <= n; i++)
    {
        printf("\nD[%d] = %d\n", i, D[i]); // printare optim
        // printare_solutie_garduri(k, i);    // printare solutie optima
    }
    printf("-----\n");
}

void sume(int v[], int n)
{
    // initializare matricea care va contine nr de sume pentru fiecare
    // pas al algoritmului
    int D[n + 1][3];
    // cazurile de baza
    D[0][0] = 0;
    D[0][1] = 0;
    D[0][2] = 0;

    /* OBSERVATIE
        Pentru a putea include si cazurile de baza in matricea
    cu numarul de sume, am inceput algoritmul de la indexul 1. Vectorul de
    numere este indexat de la 0. 
        Astfel, valoarea de la pasul curent (INDEX) din matrice este valoarea
    din vector de la (INDEX - 1).
        De aceea apare peste tot v[i - 1];
    */
    int i;
    for (i = 1; i <= n; i++)
    {
        if (v[i - 1] % 3 == 0)
        { // cazul in care v[i] % 3 da rest 0
            D[i][0] = 1 + 2 * D[i - 1][0];
            D[i][1] = 2 * D[i - 1][1];
            D[i][2] = 2 * D[i - 1][2];
        }
        else if (v[i - 1] % 3 == 1)
        { // cazul in care v[i] % 3 da rest 1
            D[i][0] = D[i - 1][0] + D[i - 1][1];
            D[i][1] = 1 + D[i - 1][0] + D[i - 1][1];
            D[i][2] = D[i - 1][2] + D[i - 1][1];
        }
        else
        { // cazul in care v[i] % 3 da rest 2
            D[i][0] = D[i - 1][0] + D[i - 1][1];
            D[i][1] = D[i - 1][2] + D[i - 1][1];
            D[i][2] = 1 + D[i - 1][2] + D[i - 1][0];
        }
    }

    printf("\nNr. sume care dau restul 0 la impartirea cu 3 este egal cu %d.\n", D[n][0]);
    printf("-----\n");
}

int main()
{
    // 1. k-garduri
    printf("\n--- K-GARDURI ---\n");
    int n = 6;       // lungime maxima a gardului
    int k = 2;       // lungimea unei singure scanduri (kx1)
    k_garduri(n, k); // apelarea functiei de rezolvare

    // 2. sume de rest 0 la impartirea cu 3
    printf("\n--- SUME MODULO 3 ---\n");
    int v[] = {3, 1, 2, 4}; // sirul de numere dat
    int len = 4;            // lungimea sirului dat
    sume(v, len);           // apelarea functiei de rezolvare
    return 0;
}
