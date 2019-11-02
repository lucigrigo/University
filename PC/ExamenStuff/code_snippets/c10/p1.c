#include<stdio.h>
#include<stdlib.h>
typedef struct {
int a,b,*x;

}
TTest;

void editTest(TTest t)
{
    t.a++;
    t.x[0]++;
printf("%d %d %d %p %p %p\n",t.a,t.b,t.x[0],&t.a,&t.b,t.x);
       


}


int main(void)
{
        TTest t;
        t.a=5;
        t.b=4;
        t.x=(int*)malloc(2*sizeof(int));
        t.x[0]=1;
        printf("%d %d %d %p %p %p\n",t.a,t.b,t.x[0],&t.a,&t.b,t.x);
        editTest(t);
        printf("%d %d %d %p %p %p\n",t.a,t.b,t.x[0],&t.a,&t.b,t.x);
        

}

