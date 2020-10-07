#include <stdio.h>

int main() 
{
    int i = 5;
    float f = (float) i;
    f = f + 0.5;
    i = (int) f;
    
    printf ("%d %f", i, f);
    getch();    
    return 0;
}
