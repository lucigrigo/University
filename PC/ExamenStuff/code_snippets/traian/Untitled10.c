#include <stdio.h>

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

int main()
{
    printf("%d %d %d %d\n", pow(2, 2), pow(2, 5), pow(2, 10), pow(2, 20));
    printf("%d %d %d %d\n", pow(3, 2), pow(3, 5), pow(3, 10), pow(3, 20));
    getch();
    return 0;
}
