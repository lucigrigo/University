#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <conio.h>
#define CLOSE_FILE 0
void verify_file(FILE* f)
{
    if (f != NULL)
    {
        printf("%p\n", f);
        if (CLOSE_FILE)
            fclose(f);
    }
    else
    {
        printf("Nu am putut deschide fisierul! Eroare: %s\n", strerror(errno));
    }    
}
int main()
{
    FILE *f1, *f2;
    f1 = fopen("Untitled20.c", "r");
    verify_file(f1);
    f1 = fopen("Untitled30.c", "r");
    verify_file(f1);
    f2 = fopen("Untitled18.c", "r");
    verify_file(f2);
    
    printf("Nr maxim fisiere deschise: %d\n", FOPEN_MAX); 
    
    getch();
    return 0;    
}
