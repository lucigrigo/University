#define MAX 3
#include<stdio.h>
#include<stdlib.h>
int main()
{
        int mat[MAX][MAX],n=3,*p,i,j;
        srand(time(NULL));
        p=mat[0];
        for(i=0;i<n;i++)
                for (j=0;j<n;j++)
                        mat[i][j]=rand()%100;
       
        for(i=0;i<n;i++)
        {
                for (j=0;j<n;j++)
                        printf("mat[i][j]=%d *(p+i*n+j)=%d\n",mat[i][j],*(p+i*n+j));
                printf("\n");
        }
        return 0;
}

