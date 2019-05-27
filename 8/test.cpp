#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <utility>
#include <algorithm>


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

template <typename iterator, typename Container, typename T>
void move_if(iterator a, iterator b, Container &o, T pred)
{
	for (auto i = a; i != b; i++)
	{
		if (pred(*i))
		o.insert(o.begin(), *i);
	}
}

int main()
{
	vector<int>v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	vector<int>v2;

	move_if(v.begin(), v.end(), v2, [](int i) { return !(i > 5); });
}
