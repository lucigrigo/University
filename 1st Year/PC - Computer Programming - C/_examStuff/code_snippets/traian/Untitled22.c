/* 
fprintf example 
Adapted from: http://www.cplusplus.com/reference/cstdio/fprintf/
*/
#include <stdio.h>
#include <string.h>

int main ()
{
   FILE * pFile;
   int i = 1;
   char name [100];

   pFile = fopen ("myfile.txt","w");
   while (1){
     puts ("please, enter a name: ");
     gets (name);
     if (strlen(name) == 0)
        break;
     fprintf (pFile, "Name %d [%-10.10s]\n", i++, name);
   }
   fclose (pFile);

   return 0;
}
