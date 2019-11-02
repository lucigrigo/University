#include <stdio.h>

int main() 
{
    char* p; 
    char sir1[] = "abcde";
    int i;
    
    for (p = sir1; *p != '\0'; p++){
        printf("%c", *(++p));
    }
    
    //printf("%s\n", sir1);
    getch();
    return 0;    
}
