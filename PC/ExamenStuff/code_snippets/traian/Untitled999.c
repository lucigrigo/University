#include <stdio.h>

#define N 5

int pow(int x, int n)
{
    if (n <= 0)
        return 1;
    int pow2 = pow(x, n/2);
    if (n % 2)
        return pow2 * pow2 * x;
    else
        return pow2 * pow2;
}

int* foo() 
{
    int v[N] = {1, 2, 3, 4, 5};
    return v;
}

print_array(int* v, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int main()
{
    int* v2 = foo();
    print_array(v2, N);
    printf("%d %d %d %d\n", pow(2, 2), pow(2, 5), pow(2, 10), pow(2, 20));
    printf("%d %d %d %d\n", pow(3, 2), pow(3, 5), pow(3, 10), pow(3, 20));
    print_array(v2, N);
    getch();
    return 0;
}
