#include <math.h>
#include <stdio.h>
#include <iostream>
#include "proc.h"

IMG::IMG (){
  cout << "Enter real part -->";
  cin >> real;
  cout << "Enter imaginary part -->";
  cin >> ipart;
}
IMG::IMG (float a, float b){ // constructor
  real = a;
  ipart = b;
};
IMG::IMG(const IMG& a) {
  real(a.real), ipart(a.ipart);
}


void IMG::multiply(float x) {
  real *= x;
  ipart *= x;
};
void IMG::plus(IMG a) {
  real += a.real;
  ipart += a.ipart;
};
void IMG::show() {
  printf("(%f, %f)", real, ipart);
}

IMG* IMG::operator *(IMG b) {
  IMG* c = new IMG(0, 0);
  c->real = (this->real * b.real) - (this->ipart * b.ipart);
  c->ipart = (this->real * b.ipart) + (b.real * this->ipart);
  return c;
};

IMG::operator double() {
  return sqrt(pow(this->real, 2) + pow(this->ipart, 2));
};
