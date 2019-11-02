#include <stdio.h>

typedef struct {
    unsigned short red : 4;
    unsigned short green : 4;
    unsigned short blue : 4;
    unsigned short other : 4;
} TColor;

void print_color(TColor color)
{
    printf("Red: %i, Green: %i, Blue: %i, Other: %i\n", color.red, color.green, color.blue, color.other);    
}

int main()
{
    TColor color;
    
    printf("Memorie ocupata: %d\n", sizeof(color));
 //   printf("Adresele sunt: %p %p %p %p\n", &color, &color.red, &color.green, &color.blue);
    print_color(color);
    color.red = 4;
    print_color(color);
    color.red = 21;
    color.green = 5;
    print_color(color);
    getch();
    return 0;    
}
