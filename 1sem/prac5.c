#include <stdio.h>

int main()
{
	int a[9]={12, 13, 14, 15, 16, 17, 18, 19, 20};
	int i, j;
	for (i=0; i<9; i++)
	{
		printf("%d|", a[i]);
	}
	printf("\n");
	int a1[2][2] = {{1, 1},{0, 1}};
	int a2[2][2] = {{2, 0},{3, 0}};
	for (i=0; i<2; i++)
	{
		for (j=0; j<2; j++)
		{
			printf("%d ", a1[i][0]*a2[0][j]+a1[i][1]*a2[1][j]);
		}
		printf("\n");
	}
}
