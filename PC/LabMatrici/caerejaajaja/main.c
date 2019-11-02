#include <stdio.h>
#include <stdlib.h>
#define MAX 1002

void problema1();
void problema2();
void problema3();
int dreapta(int A[MAX][MAX],
            int j,
            int k)
{
    if(A[j][k+1] == -1)
    {
        return -1;
    }
    if(A[j][k+1])
    {
        return 0;
    }
    return 1;
}

int main()
{
    //problema1();
    //problema2();
    problema3();
    return 0;
}

void problema1()
{
    //citeste n si o matrice nxn. afis suma pe linii si pe coloane
    int n, A[MAX][MAX], i, j, col, lin;
    printf("Dati n:");
    scanf("%d",&n);
    for(i = 0; i < n ; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d",&A[i][j]);
        }
    }
    for(i = 0; i < n; i++)
    {
        col = 0;
        lin = 0;
        for(j = 0; j < n; j++)
        {
            col += A[j][i];
            lin += A[i][j];
        }
        printf("Suma elementelor de pe coloana %d=%d\n", i, col);
        printf("Suma elementelor de pe linia %d=%d\n", i, lin);

    }

}

void problema2()
{
    //defineste si initializeaza doua matrici M (2x4),N(4x2)
    //afiseaza produsul
    int i, j, k, M[MAX][MAX], N[MAX][MAX], m, n, x;
    printf("Dati m,n:");
    scanf("%d%d",&m,&n);
    printf("Dati matricea M de dimensiune %d x %d: ",m,n);
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d",&M[i][j]);
        }
    }
    printf("Dati matricea N de dimensiune %d x %d: ",n,m);
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d",&N[i][j]);
        }
    }
    for(i = 0; i < m; i++)
    {
        for(k = 0; k < m; k++)
        {
            for(j = 0, x = 0; j < n; j++)
            {
                x += M[i][j] * N[j][k];
            }
            printf("%d ", x);
        }
        printf("\n");
    }

}
void problema3()
{
    // dreapta = 1 jos = 2 stanga = 3 sus = 4
    int i, j, k, n=1000, A[MAX][MAX], dir=0;
   // scanf("%d", &n);
    A[1][1]=1;
    /*for(i = 2, j=1, k = 2; i <= n; i++)
    {
        if((dir%4) == 1)
        {
            if(dreapta(A,j,k))
            {
                A[j][k++]=i;
                if(-1 == dreapta(A,j,k))
                {
                    dir++;
                    j++;
                }
            }
        }
    }*/
    for(i = 0; i < n+2; i++)
    {
        A[0][i]=-1;
        A[i][0]=-1;
        A[n+1][i]=-1;
        A[i][n+1]=-1;
    }
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <=n; j++)
        {
            A[i][j]=0;
        }
    }
    k=1;
    i=j=1;
    while(k < ((n*n)+1))
    {
        A[i][j]=k;
        k++;
        if((dir%4) == 0)
        {
            if(A[i][j+1] == 0)
            {
                j++;
            }
            else
            {
                dir++;
                if(A[i+1][j] == 0)
                {
                    i++;
                }
                else
                {
                    i--;
                }
            }
            continue;
        }
        if((dir%4) == 1)
        {
            if(A[i+1][j] == 0)
            {
                i++;
            }
            else
            {
                dir++;
                if(A[i][j+1] == 0)
                {
                    j++;
                }
                else
                {
                    j--;
                }
            }
            continue;
        }
        if((dir%4) == 2)
        {
            if(A[i][j-1] == 0)
            {
                j--;
            }
            else
            {
                dir++;
                if(A[i+1][j] == 0)
                {
                    i++;
                }
                else
                {
                    i--;
                }
            }
            continue;
        }
        if((dir%4) == 3)
        {
            if(A[i-1][j] == 0)
            {
                i--;
            }
            else
            {
                dir++;
                if(A[i][j+1] == 0)
                {
                    j++;
                }
                else
                {
                    i--;
                }
            }
            continue;
        }

    }
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j<=n; j++)
        {
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
}
