#include <stdio.h>
#include <conio.h>
#include <stdarg.h>

int op_int(char op, ...)
{
    int result;
    int i;
    va_list ap;
    
    va_start(ap, op);    
    switch (op)
    {
        case '+': 
            result = 0; 
            break;
        case '*':
            result = 1;
            break;
    }
    while (1)
    {
        i = va_arg(ap, int);
        if (i < 0)
            break;
        switch (op)
        {
            case '+': 
                result += i; 
                break;
            case '*':
                result *= i;
                break;
        } 
    }
    va_end(ap);
    return result;
}

int main()
{
    int result;
    result = op_int('+', 1, 2, 3, 4, 5, -1);
    printf("%d\n", result);
    result = op_int('*', 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1);
    printf("%d\n", result);
    getch();
    return 0;    
}
