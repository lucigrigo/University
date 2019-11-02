#include<stdio.h>
#include<string.h>


int main()
{
        char s1[50], s2[]="sirul s2";
        char *p1=s1;
        printf("%s\n%s\n",s1,s2);
        printf("%i %i\n",sizeof(s1), strlen(s1));
        printf("%i %i\n",sizeof(s2), strlen(s2));
        printf("%p %p %p %p\n %i ",p1,&p1,s1,&s1,'\0');
        return 0;
}
