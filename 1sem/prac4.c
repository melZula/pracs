#include <stdio.h>

int main()
{
	int n;
	scanf("%d", &n);
	printf ("%d\n",((n>33)&&(n<55)));

	int k;
	scanf("%d", &k);

	int b = k>>14;
	printf("%d\n", b%2);
	return 0;
}
