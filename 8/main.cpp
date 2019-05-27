#include <iostream>
#include <vector>

using namespace std;

class CPoint {
public:
  float x;
  float y;
  bool operator== (CPoint& ptr){
    return (this->x == ptr.x && this->y == ptr.y);
  };
};

////////////////////////////////  algo: any_of , predicate: GreaterThan10
template <typename T>
class GreaterThan10 {
public:
bool operator()(T x) const { return x > 10; }
};

template<typename Iter, class Predicate>
bool any_of(Iter first, Iter last, Predicate f) {
  while (first != last) {
    if (f(*first)) {
      return true;
    }
    first++;
  }
  return false;
}

//////////////////////////////// algo: is_sorted , condition: std::less
/*
template<typename T>
struct less_equal{
bool operator()(const T &lhs, const T &rhs) const {
    return lhs <= rhs;
}
};
*/

template<typename Iter, typename F>
bool is_sorted(Iter first, Iter last, F pred) {
  while (first != last-1) {
    if (!pred(*first, *(first+1) )) {
      return false;
    }
    first++;
  }
  return true;
}
////////////////////////////////// algo: is_palindrome ,
template<typename Iter>
bool is_palindrome(Iter first, Iter last) {
  while (first < last) {
    if (*first != *(last-1)) {
      return false;
    }
    first++;
    last--;
  }
  return true;
}

int main() {
  vector<float> v = {1, 2, 4, 5, 6, 6, 7.25, 10.25};
  vector<int> v2 = {5, 4, 3, 2, 1, 1, 2, 3, 4, 5};
  vector<int> v3 = {1, 2, 3, 2, 1};
  vector<CPoint> v4(5);
  for (size_t i = 0; i < 5; i++) {
    cin >> v4[i].x;
    cin >> v4[i].y;
  }

  cout << any_of(v.begin(), v.end(), GreaterThan10<float>()) << endl;
  cout << is_sorted(v.begin(), v.end(), less_equal<float>()) << endl;
  cout << is_palindrome(v2.begin(), v2.end()) << endl;
  cout << is_palindrome(v3.begin(), v3.end()) << endl;

  return 0;
}
