#include <stdio.h>
#include <string.h>

int main()
{
	char a[10], b[10];
	scanf("%s", a);
	scanf("%s", b);
	printf("%s%s\n", a, b);
	
	int n;
	scanf("%d", &n);
	if (strncmp (a, b, n)==0)
        	printf ("Совпадают\n");
	else
		printf ("Отличаются\n");
		
	printf("%d %d\n", strlen(a), strlen(b));
	
	int istr;
	istr = strcasestr (a,b);
	if ( istr == NULL)
		printf ("Строка не найдена\n");
	else
		printf ("Найдена\n");
		
	printf("length od segment: %d\n", strcspn(a,b));
}
