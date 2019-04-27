#include <stdio.h>
#include <iostream>
#include <math.h>
#include "proc.h"

struct img{
  float real;
  float ipart;
  operator double() {
    return sqrt(pow(this->real, 2) + pow(this->ipart, 2));
  }
};

class IntStack {
public:
  IntStack(int num) {  top = 0; maxelem = num; s = new int[maxelem]; }
  void operator << (int t) {
    if (top == maxelem) return;
    s[top++] = t;
  }
  int pop() {
    if (top == 0) return -1;
    return s[--top];
  }
  void operator >>(int t) {
    if (top == 0) return;
    for (size_t i = 0; i < t; i++) {
      pop();
    }
  }

  void display() {
    if (top == 0) { printf("(empty)\n");  return; }
    for (int t=0 ; t < top ; t++) printf("%d ", s[t]);;
    printf("\n");;
  }
  int empty()  {  return top == 0;  }

private:
  int *s;
  int top;
  int maxelem;
};



int main()
{
  float x, y, z, x2, y2;
  printf("input real part >");
  scanf("%f", &x);
  printf("input img part >");
  scanf("%f", &y);
  img test = {x, y};
  printf("input multiply >");
  scanf("%f", &z);
  img *answ = test * z;
  printf("1: (%f,%f)*%f=(%f, %f)\n",x, y, z, answ->real, answ->ipart);

  printf("input real part 2>");
  scanf("%f", &x2);
  printf("input img part 2>");
  scanf("%f", &y2);
  img test2 = {x2, y2};
  img* answ2 = test * test2;
  printf("2: (%f,%f)*(%f,%f)=(%f, %f)\n",x, y, x2, y2, answ2->real, answ2->ipart);

  z = (double)test;
  printf("3: length(%f,%f)=%f\n",x, y, z );


  IntStack* s = new IntStack(100);
  int n;
  printf("Enter numbers in stack(0 to stop):\n");
  scanf("%d",&n );
  while (n != 0) {
    *s << n;
    scanf("%d", &n);
  }
  s->display();
  printf("How many numbers pop() >\n");
  scanf("%d", &n);
  *s >> n;
  s->display();
}
// g++ -c proc.h -o proch
// g++ -c proc.cpp -o proc.o -lm
// g++ main.cpp proc.o -o main -lm
