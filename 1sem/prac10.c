#include <stdio.h>

int sumnum(int n)
{
	if (n > 0)
		return (n % 10 + sumnum(n / 10));
	else
		return 0;
}

int nums(int n)
{
	int i;
	int arr[10];
	
	for (i = 0; i<sizeof(n)-1; i++)
	{
		arr[i] = n % 10;
		n = n / 10;
		printf ("%d ", arr[i]);	
	}
}

int main()
{	
	int a;
	scanf ("%d", &a);
	printf("%d\n", sumnum(a));
	
	nums(a);
}



/*int j = 0;
char* exspace(char str[], int i)
{
	if (i < 10)
	{
		if (str[i] == ' ') 
		{
			if (j == 0) return (exspace(str, i++));
			if (str[i+1] == ' ') return (exspace(str, i++));
		}
		j++;
		return (str[i] + exspace(str, i++));
	}
	else
		return 0;
}*/
