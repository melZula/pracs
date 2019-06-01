#include <iostream>
#include <iterator>
#include <math.h>

using namespace std;

template<class T, class Compare = std::less<T>>
class BST {
public:
  typedef const iterator<T, Compare> const_iterator;
  int size;
  T* mem = (T*)malloc(3*sizeof(T));

  BST() {
    size = 0;
    T mem[size];
    cout << "New BST" << endl;
  };
  BST(const BST &bst) :
  size(bst.size),
  mem(bst.mem)
  {
    cout << "Copy success " << endl;
  };
  BST& operator=(const BST &){
    /// ----
  };

  void show() {
    for (size_t i = 0; i < size; i++) {
      cout << mem[i] << " ";
    }
    cout << endl;
    /*
    for (auto it = cbegin(); it < end(); it++) {
    cout << *it << " ";
  }*/
};

template<class InputIt>
void assign(InputIt first, InputIt last){
  // ???
};

iterator<T, Compare> begin(){
  return &mem[0];
};

const_iterator cbegin() const{
  return &mem[0];
};
iterator<T, Compare> end(){
  return &mem[size];
};

const_iterator cend() const{
  ///
};

iterator<T, Compare> insert(const T &value){ // use iterators
  int i = 0;
  Compare which;
  while ((mem[i]!=-100000)&&(i < size)) {
    if (which(mem[i], value)) {
      i = i * 2 + 2;
    } else
    i = i *2 + 1;
  }
  cout << "i = " << i << endl;
  if (i >= size) {
    cout << "resize... ";
    int new_size = size * 2 + 1;
    void* p = realloc(mem, new_size);
    if (p == NULL) {
      cout << "Bad realloc ";
    }
    for (T* t = mem+size; t < mem+new_size; t++) {
      *t = -100000;
    }
    size = new_size;
    cout << "Resize to " << size << endl;
  }
  mem[i] = value;
  cout << "Inserted" << endl;
  return &mem[i];
};
/*
iterator remove(const T &value);
iterator find(const T &value);
const_iterator find(const T &value) const;
bool empty() const;
size_t size() const;*/
};

int main(int argc, char const *argv[]) {
  BST<int> tree;
  //
  cout << "size = " << tree.size << endl;
  cout << "SIZE " << (sizeof(tree.mem)/sizeof(*(tree.mem))) << endl;
  tree.insert(1);
  tree.show();
  tree.insert(-4);
  tree.show();
  tree.insert(4);
  tree.show();
  tree.insert(7);
  tree.show();

  free(tree.mem);
  return 0;
}
