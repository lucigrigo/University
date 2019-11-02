int main() 
{
    int v[10][10];
    int **p = v;
    int **p1 = (int**)malloc(10*sizeof(int*));
    for (int i = 0; i < 10; i++)
        p1[i] = (int*)malloc(10*sizeof(int));
        
    printf("%p %p\n", v, p);
    printf("%p %p\n", &v, &p);
    printf("\n");
    for (int i = 0; i < 10; i++)
        printf("%p %p\n", v[i], p1[i]);
        
    printf("\n");
    for (int i = 0; i < 10; i++)
        printf("%p %p\n", &v[i], &p1[i]);
    
    return 0;
}