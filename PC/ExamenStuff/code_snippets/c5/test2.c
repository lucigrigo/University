#include <stdio.h>
#include <stdlib.h>

int cut(int**v,int n)
{
    (*v)++;
    return n-1;
}

int main()
{
        int v[50],i,*p,n;
        srand(time(NULL));
        n=10+rand()%10;
        for (i=0;i<n;i++)
        {
                v[i]=rand()%100;
        }
        for (i=0;i<n;i++)
        {
                printf("%d ",v[i]);
        }
        p=v;
        printf("\n");
        n=cut(&p,n);
        for (i=0;i<n;i++)
        {
                printf("%d ",p[i]);
        }
        

}
