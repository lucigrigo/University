#include <stdio.h>
#include <stdlib.h>
#define MAX 50
int insertSort(int *v, int n)
{
        int val, pos, count=0,i;
        for(i=1;i<n;i++)
        {
                val=v[1];
                pos=i;
                while(pos>0 && val<v[pos-1])
                {
                        v[pos]=v[pos-1];
                        pos--;
                        count++;
                }
                v[pos]=val;
        }
        return count;
}

int comparaCresc(const void*a, const void*b)
{
        int *x= (int*)a, *y=(int*)b;
        return *x-*y;
}

int comparaDescresc(const void*a, const void*b)
{
        int *x= (int*)a, *y=(int*)b;
        return *y-*x;
}

int main()
{
        int nrEl,nrOp,i, v[MAX];
        srand(time(NULL));
        nrEl=10+rand()%40;//vectori intre 10 si 50 el
        for(i=0;i<nrEl;i++)
        {
                v[i]=rand()%100;
                printf(" %d",v[i]);
        }
        printf("\n");

        nrOp=insertSort(v,nrEl);
        for(i=0;i<nrEl;i++)
                printf(" %d",v[i]);
        printf("\n");
        qsort(v, nrEl,sizeof(int),comparaDescresc);
        for(i=0;i<nrEl;i++)
            printf(" %d",v[i]);
        printf("\n");
        qsort(v, nrEl,sizeof(int),comparaCresc);
        for(i=0;i<nrEl;i++)
            printf(" %d",v[i]);
 

        printf("\nnr elemente=%d, nr operatii=%d, nrOp/nrEl=%f",nrEl,nrOp, nrOp/(float)nrEl);
        return 0;

}
