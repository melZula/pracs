#include <stdio.h>
#include <math.h>
#include "proc.h"


int main() {
  float x, y, z;
  printf("Enter real part >");
  scanf("%f", &x);
  printf("Enter imaginary part >");
  scanf("%f", &y);
  IMG* test = new IMG(x, y);
  IMG num = *test;
  printf("Enter multiplier >");
  scanf("%f", &z);
  num.show();
  num.multiply(z);
  printf("*%f = ",z);
  num.show();
  printf("\n");

  printf("Enter real part >");
  scanf("%f", &x);
  printf("Enter imaginary part >");
  scanf("%f", &y);
  IMG num2 = *(new IMG(x, y));
  num.show();
  printf(" + ");
  num2.show();
  printf(" = ");
  num.plus(num2);
  num.show();
  printf("\n");

  num.show();
  printf(" * ");
  num2.show();
  printf(" = ");
  IMG* result = num * num2;
  result->show();
  printf("\n");

  float len, len2;
  len = (double)num;
  len2 = (double)num2;
  printf("length ");
  num.show();
  printf("= %f\n", len);
  printf("length ");
  num2.show();
  printf("= %f\n", len2);
  return 0;
}
