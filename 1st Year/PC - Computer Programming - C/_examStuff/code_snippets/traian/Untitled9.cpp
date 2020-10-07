#include <stdio.h>

int main()
{
    char* p_char;
    int * p_int;  
    double *p_double;
    
    int x = 5;
    
    printf("%d %d %d %d\n", sizeof(p_char), sizeof(p_int), sizeof(p_double), sizeof(void*));
    printf("%p %p %p\n", p_char, p_int, p_double);
    
    scanf("%d", p_int);
    printf("%d %p\n", *p_int, p_int);
    scanf("%d", p_int);
    
//    p_char = &x;
}
