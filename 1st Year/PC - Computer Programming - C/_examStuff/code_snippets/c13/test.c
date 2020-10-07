#include "recapitulare.h"
#include<stdio.h>
int main()
{
        Unit u1[3]={{7,"Zergling", 2,6,40},{2,"Hydra",7,15,100}, {1,"Ultra",40,60,500}};
        int nr=3;
        FILE*f=fopen("test.bin","wb");
        fwrite(&nr,sizeof(int),1,f);
        fwrite(u1,sizeof(Unit),3,f);
        fclose(f);
        return 0;
}
