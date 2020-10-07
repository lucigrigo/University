#include <stdio.h>

void noswap(char *t1, char *t2)
{
    char *t;
    t = t1;
    t1 = t2;
    t2 = t;
}
void swap(char *t1, char *t2)
{
    char *t;
    t = *t1;
    *t1 = *t2;
    *t2 = t;
}
int main()
{
    char *ptr[2] = {"hello", "morning"};
    noswap(ptr[0], ptr[1]);
    printf("%s %s \n", ptr[0], ptr[1]);
    swap(&ptr[0], &ptr[1]);
    printf("%s %s \n", ptr[0], ptr[1]);
    return 0;
}
