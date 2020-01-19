#include <stdio.h>

typedef struct {  short y;int x; char c;}TPct;
int main()
{
        TPct p={.x=3,.y=7};
        printf("%d %d %d",p.x,p.y, sizeof(p));
}
