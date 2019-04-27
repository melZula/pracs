#include "proc.h"

#define SWAP(A, B) { float t = A; A = B; B = t; }

struct circle{
  float x;
  float y;
  float r;
};

void proc_3(int* a ,int* b) {
  if (*a > *b) {
    *a = *a % *b;
  }
  else
   *b = *b % *a;
}

void proc_3ref(int& a, int& b){
  if (a > b) {
    a = a % b;
  }
  else
   b = b % a;
}

void proc_6(float* x) {
  *x = (int)(*x + 0.5);
}

void proc_6ref(float& x) {
  x = (int)(x + 0.5);
}

void proc11(circle* c, float* x) {
  c->r -= *x;
}

void proc11ref(circle& c, float& x) {
  c.r -= x;
}
