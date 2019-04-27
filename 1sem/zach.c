#include <stdio.h>

int evkl(int a, int b){
  if ((a > 0)&&(b > 0))
  return ((a > b) ? evkl(a-b, b) : evkl(a, b-a));
}

int main(){
  printf("%d\n", evkl(48, 36));
}
