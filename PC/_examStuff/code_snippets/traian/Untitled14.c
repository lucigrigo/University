#include <stdio.h>

int main() 
{
    int x = 5;
    int& a = x;
    a++;
    
    printf("%d %d\n", a, x);
    
    return 0; 
}
