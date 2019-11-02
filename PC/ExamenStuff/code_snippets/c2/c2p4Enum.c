/*playing with enum type */
#include <stdio.h>

int main()
{
	enum bool{false, true};//false are valoarea 0, true are valoarea 1
	enum bool a=false;
	printf("a=%d\n",a);
	a+=1;
	printf("a=%d\n",a);
	a=true;
	printf("a=%d\n",a);
	
	enum calificativ{ns=4,s=5,b=8,fb=10};
	int notaStud1=ns,notaStud2=s, notaStud3=b, notaStud4=fb;
	
	printf("nota Student1:%e\n",notaStud1*1.20);
	printf("nota Student2:%d\n",notaStud2);
	printf("nota Student3:%d\n",notaStud3);
	printf("nota Student4:%d\n",notaStud4);
	return 0;

}
