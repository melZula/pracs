#include <iostream>
#include <string>
#include <exception>

using namespace std;

template <typename T>
T mini(const T a, const T b){
  return (a < b) ? a : b;
}

class StackException: public std::exception
{
private:
  string m_error;

public:
  StackException(std::string error): m_error(error){}

  const char* what() const noexcept { return m_error.c_str(); }
};


template <int maxelem, class E>
class Stack {
public:
  Stack() {  top = 0; s = new E[maxelem]; };
  void push (E t) {
    if (top == maxelem) throw StackException("Stack overflow");
    s[top++] = t;
  }
  E pop() {
    if (top == 0) throw StackException("No elements");
    return s[--top];
  }
  E front() {
    if (top == 0) throw StackException("No elements");
    return s[top-1];
  }
  void display() {
    if (top == 0) { printf("(empty)\n");  return; }
    for (int t=0 ; t < top ; t++) cout << s[t] << ' ';
    printf("\n");
  }
  int empty()  {  return top == 0;  }

private:
  E *s;
  int top;
  //int maxelem;
};




int main() {
  float a = 5;
  float b = 8;
  cout << mini(a, b);


  Stack<3, double> s;
  double n;

  try {
    printf("Enter in stack(0 to stop):\n");
    cin >> n;
    while (n) {
      s.push(n);
      cin >> n;
    }
    s.display();
    cout << "pop x3...";
    s.pop();
    s.pop();
    s.pop();
    s.display();
  }
  catch (StackException &exception)
  {
    cout << "Error: " << exception.what() << "\n";
  }
  return 0;
}
