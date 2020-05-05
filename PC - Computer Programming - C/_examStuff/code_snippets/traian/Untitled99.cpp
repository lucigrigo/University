int f ()
{        
	static int c;
	return ++c; 
}
int main(void)
{
        	int x;
 	printf("%d %d\n",  f(), f()+f() );
 	getch()
	return 0;
}

