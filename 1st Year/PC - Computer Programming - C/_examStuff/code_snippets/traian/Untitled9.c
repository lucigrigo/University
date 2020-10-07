#include <stdio.h>

int main()
{
    int v[20] = {1,2,3,4};
    char* p_char;
    int * p_int;  
    double *p_double;
    void* p_void;
    
    int i = 3;
    
    printf("%d %d %d\n", v[-1], v[20], v[i++]++);
    
    int x = 5;
    
    printf("%d %d %d %d\n", sizeof(p_char), sizeof(p_int), sizeof(p_double), sizeof(void*));
    printf("%p %p %p\n", p_char, p_int, p_double);
    
    scanf("%d", p_int);
    printf("%d %p\n", *p_int, &p_int);
    scanf("%d", p_int);
    
    p_void = &x;
    p_int = &x;
    printf("%p %p %p %p %d\n", p_void, p_int, p_void + 1, p_int + 1, p_int - (p_int + 1));
    
    getch();
    return 0;
}
