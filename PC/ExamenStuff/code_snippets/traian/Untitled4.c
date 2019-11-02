#include <stdio.h>

int main()
{
    int x = 1;
    printf("x = 5 : %d , x == 0 : %d , x = 0 : %d , x == 0 : %d \n", 
            x = 5, 
            x == 0, 
            x = 0, 
            x == 0
    );
    
    int i, j, k;
    for (i = 0, j = 1, k = 0; i < 5; i++, j *= 2)
    {
        printf("%d %d\n", j, k++);
    }
        
    scanf("%d", &x); 
    
    return 0;    
}
