./prac9#include <stdio.h>
#include <math.h>

int main()
{
	int i, j, n;
	scanf("%d", &n);
	int flag;
	for (i = 2; i<n+1; i++)
	{
		flag = 0;
		for (j = 2; j<=sqrt(i); j++)
		{
			if (i%j == 0) flag = 1;
		}
		if (flag == 0) printf("%d\n", i);
	}
	
	float inrate, sum;
	int months;
	scanf("%f %f %d", &inrate, &sum, &months);
	for (i = 0; i<months; i++)
	{
		sum = sum*(1 + inrate/100);
		printf("month:%d - sum = %4.2f\n", i+1, sum);
	}
	
	return 0;
}
