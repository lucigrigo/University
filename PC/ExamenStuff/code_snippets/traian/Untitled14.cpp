#include <stdio.h>
#include <conio.h>


int main() 
{
    int x = 5;
    int& a = x;
    a++;
    
    printf("%d %d %p %p\n", a, x, &a, &x);
    getch();
    return 0; 
}
