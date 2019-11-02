//
//  main.c
//  prob1lab7
//
//  Created by Grigore Lucian on 12/10/2018.
//  Copyright © 2018 Grigore Lucian. All rights reserved.
//

#include <stdio.h>

void print_bits(int x,int nrbits)
{
    int i;
    for(i=nrbits-1;i>=0;i--)
    {
        printf("%u" , ((x>>i)&1));
    }
    printf("\n");
}

void powerbits(int k)
{
    k=1<<k;
    printf("2^k = ");
    print_bits(k,32);
}

void cerintaC(int a,int b)
{
    a<<=b;
    print_bits(a,32);
    a>>=b;
    a>>=b;
    print_bits(a,32);
}

void cerintaD(int n,int k)
{
    int x=(n>>(k-1))&1;
    int y=(n>>(k+1))&1;
    if(x!=y)
    {
        if(x)
        {
            int mask=~(1<<(k-1));
            n=n&mask;
            mask=1<<(k+1);
            n=n|mask;
            print_bits(n, 32);
        }
        else
        {
            int mask=(1<<(k-1));
            n=n|mask;
            mask=~(1<<(k+1));
            n=n&mask;
            print_bits(n, 32);
        }
    }
    else
    {
        print_bits(n,32);
    }
}

void cerintaE(int n,int k)
{
    
}

void cerintaF(int n)
{
    int nr=0;
    for(int i=31;i>=0;i--)
    {
        if((n>>i)&1)
        {
            nr++;
        }
    }
    printf("%d",nr);
}

void cerintaG(int n,int k)
{
    int a=1<<k;
    if(n>=a)
    {
        while((a<<k)<=n)
        {
            a<<=k;
        }
        print_bits((n-a),32);
    }
    else
    {
        print_bits(n,32);
    }
}

int main()
{
    int n ,k  ;
    printf("Dati n si k , in aceasta ordine : ");
    scanf("%d %d", &n , &k);
    //print_bits(n, 32);    //cerintaA
    //powerbits(k);     //cerintaB
    //cerintaC(n,k);
    //cerintaD(n,k);
    //cerintaE(n,k);
    //cerintaF(n);
    cerintaG(n,k);
    return 0;
}
