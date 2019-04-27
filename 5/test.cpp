#include <iostream>

class suka {
public:
  int blyat;
  suka(int n) {
    blyat = n;
  }
};

int main(){
  std::cout << "sasattt " << '\n';
  suka cpp(7);
  std::cout << "Suka " << '\n';
  std::cout << cpp.blyat << '\n';
  return 0;
}
