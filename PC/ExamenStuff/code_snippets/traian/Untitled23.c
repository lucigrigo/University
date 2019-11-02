#include <stdio.h>

int main()
{
    FILE *f = fopen("myfile2.txt", "w");
    if (f){
        fputc('a', f);
        sleep(10000);
        fflush(f);
        sleep(10000);
        fclose(f);
    }
    return 1;
}
