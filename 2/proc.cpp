#include "proc.h"
#include <stdio.h>
#include <math.h>

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

img* operator * (img a, float b) {
  img *c = new(img);
  c->real = a.real * b;
  c->ipart = a.ipart * b;
  return c;
}

img* operator * (img a, img b) {
  img *c = new(img);
  c->real = (a.real * b.real) - (a.ipart * b.ipart);
  c->ipart = (a.real * b.ipart) + (b.real * a.ipart);
  return c;
}
