#include <stdio.h>
#include <math.h>
#include "proc.h"

struct circle{
  float x;
  float y;
  float r;
};

int main()
{
  int a;
  int b;
  printf("input a =");
  scanf("%d", &a);
  printf("input b =");
	scanf("%d", &b);

	int* pa = &a;
	int* pb = &b;
	proc_3(pa, pb);
	printf("3.1: max(a,b) mod min(a,b) a=%d b=%d\n", a, b);

	proc_3ref(a, b);
	printf("3.2: max(a,b) mod min(a,b) a=%d b=%d\n", a, b);

  float f;
  printf("input float f=");
	scanf("%f", &f);
	float* pf = &f;
	proc_6(pf);
	printf("6.1: round(f) = %f\n", f);

  float f2;
  printf("input float f2=");
	scanf("%f", &f2);
	proc_6ref(f2);
	printf("6.2: round(f2) = %f\n", f2);

	circle c;
	circle* pc = &c;
	pc->x = a;
	pc->y = b;
	pc->r = f2;
	proc11(pc, pf);
	printf("11.1: radius(f2 - f) = %f\n", pc->r);

  float f3 = 0.25;
	proc11ref(c, f3);
	printf("11.2: radius(r - 0.25) = %f\n", c.r);

}
// g++ -c proc.h -o proch
// g++ -c proc.cpp -o proc.o -lm
// g++ main.cpp proc.o -o main -lm
