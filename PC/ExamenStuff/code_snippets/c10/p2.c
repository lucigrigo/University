#include <stdio.h>

int main()
{
        FILE*f =fopen("Dillon.mp3","r+b");
        long position=0;char tag[4], title[31]="testtitle100000011";
        if(!f)
        {
                printf("nu s-a putut deschide");
                return -1;
        }

        fseek(f,0,SEEK_END);
       position=ftell(f);
       fseek(f,position-125,SEEK_SET);
       //fread(tag,1,3,f);
       //tag[3]='\0';
       fwrite(title,1,30,f);
       fclose(f);
       //printf("tag: %s\n",tag);
}
