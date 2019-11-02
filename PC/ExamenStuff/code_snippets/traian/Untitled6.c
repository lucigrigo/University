#include <stdio.h>

int main()
{
	int a=5, b=6, first = 0;
    if (first){ 
        printf("%d+%d=%d\n", ++a, b++, a + b);
    }else{
        printf("%d=%d+%d\n", a + b, ++a, b++);
    }
    
    scanf("%d", &a);
    
    return 0;
}
