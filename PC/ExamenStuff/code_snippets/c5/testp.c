#include <stdio.h>

int main()
{
        int x[5],*p=x;
        printf("x=%p p=%p\n",x,p);
        printf("x+1=%p p+1=%p\n",x+1,p+1);
        printf("&x=%p &p=%p\n",&x,&p);
        printf("&x+1=%p &p+1=%p\n",&x+1,&p+1);
        printf("sizeof(x)=%d, sizeof(p)=%d\n",sizeof(x), sizeof(p));
        return 0;
}
