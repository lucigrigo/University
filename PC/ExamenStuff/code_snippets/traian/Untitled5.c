#include <stdio.h>

int fun(int i)
{
    return (i++); 
}
int main()
{
    int i = fun(10);
    printf("%d\n", --i);
    
    scanf("%d", &i);
    
    return 0;
}
