#ifndef IMG_H
#define IMG_H

class IMG {
public:
  IMG::IMG ();
  IMG (float a, float b);
  IMG::IMG(const IMG a);
  void multiply(float x);
  void plus(IMG a);
  void show();
  IMG* operator *(IMG b);
  operator double();
private:
  float real;
  float ipart;
};

#endif
