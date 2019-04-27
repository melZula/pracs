#include <stdio.h>
#include <math.h>
#include "prac11.h"

int main()
{
	struct figure fig;
	fig.x1 = 4;
	fig.y1 = 5;
	fig.x2 = 3;
	fig.y2 = 6;
	fig.x3 = 2;
	fig.y3 = 5;
	
	printf("%f", sq(fig));
	return 0;
}
// gcc -c prac11.h -o prac11_h.o
// gcc -c prac11.c -o prac11.o -lm
// gcc prac11main.c prac11.o -o prac11main -lm

