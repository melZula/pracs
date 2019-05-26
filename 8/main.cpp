#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<class IT, class KEY>
bool binary_search(IT first, IT last, KEY key)
{
  // element not found
  if (first == last)
  return false;
  // check for the desired element
  IT half = first;
  advance(half, distance(first, last) / 2);
  if (key == *half)
  return true;
  // recursive call
  if (key < *half)
  return binary_search(first, half, key);
  return binary_search(++half, last, key);
};


template <typename T>
bool pred(const T a){
  return (a > 10);
}
void (*funcptr)(const T a);

template<typename Iter, typename Func>
bool any_of(Iter first, Iter last, Func& f) {
  while (first != last) {
    if (f(*first)) {
      return true;
    }
  }
  return false;
}

int main() {
  vector<int> v = {1, 2, 4, 5, 6, 7, 11};


  //cout << any_of(v.begin(), v.end(), pred()) << endl;

  return 0;
}
