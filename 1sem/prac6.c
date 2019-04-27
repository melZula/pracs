#include <stdio.h>
#include <malloc.h>

int main()
{
	char c[5]="Hello";
	int i;
	char *pc;
	pc = &c[0];
	for (i=0; i<5; i++)
	{
		printf("%c|", *(pc+i));
	}
	
	char *p;
	p = (char*)malloc(5*sizeof(char));
	p = "Hello";
	for (i=0; i<5; i++)
	{
		printf("%c|", *(p+i));
	}
	
	return 0;
}
