#include <stdio.h>
char* test(void)
{
        char s[]="abcabc";
        return s;
}
int main()
{
    char s[5],*p;
    fgets(s,5,stdin);
    puts(s);
    printf("\n%i %i\n", sizeof(s), strlen(s));
    p=test();
    printf("%s", test);
    return 0;
}
