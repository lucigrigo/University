#include <stdio.h>
#include <string.h>
 
union Data {
   int i;
   float f;
   char str[20];
};

void print_data(union Data data)
{
   printf( "data.i : %d\n", data.i);
   printf( "data.f : %f\n", data.f);
   printf( "data.str : %s\n", data.str);

}
 
int main( ) {

   union Data data;        

   printf( "Memory size occupied by data : %d\n", sizeof(data));
   printf( "Pointers to data: %p %p %p %p\n", &data, &data.i, &data.f, &data.str);
   
   data.i = 10;
   print_data(data);
   data.f = 220.5;
   print_data(data);
   strcpy( data.str, "C Programming");
   print_data(data);

   getch();
   return 0;
}
