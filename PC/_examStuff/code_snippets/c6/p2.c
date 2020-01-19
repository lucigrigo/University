#include<stdio.h>

int main()
{
        char s[]="ana si ana banana", *p=s;
        int count=0;
        for(;*p!='\0';)
        {
            p=strstr(p,"ana");
            if (p==NULL)
                    break;
             printf("%s\n",p);
            count++;
            p+=strlen("ana");
        }        
        return;
}

