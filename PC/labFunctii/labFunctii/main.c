#include <stdio.h>
#include <stdlib.h>

int fib(int n)
{
    int a=0,b=1,c=0;
    if( n==0 )
    {
        return 0;
    }
    else
    {
        int contor = 1;
        for(;contor < n;)
        {
            a = b + c;
            b = c;
            c = a;
            contor++;
        }
    }
    return a;
}

int fibrecursiv(int n)
{
    if(n==2)
    {
        return 1;
    }
    if(n==1)
    {
        return 0;
    }
    else
    {
        return (fibrecursiv(n-1) + fibrecursiv(n-2));
    }
}

int inlocuire(int nr,
              int c1,
              int c2)
{
        if(nr!=0)
        {
            if ((nr%10)==c1)
            {
                return c2 + 10 * inlocuire(nr/10, c1, c2);
            }
            else
            {
                return nr % 10 + 10 * inlocuire(nr/10, c1, c2);
            }
        }
        else return 0;
}

int main()
{
    printf("%d\n",fib(5));
    printf("%d\n",fibrecursiv(5));
    printf("%d\n",inlocuire(2342572, 2, 8));
    return 0;
}
