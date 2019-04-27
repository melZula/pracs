#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

struct point{
  double x;
  double y;
}; // структура точки

float len(point a, point b) {
  return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2))  ;
} // функция длины


// площадь и периметр, масса
class IGeoFig {
public:
  virtual double square() = 0;
  virtual double perimetr() = 0;
  virtual int mass() = 0;
};

// Интерфейс для классов, которые можно задать через диалог с пользователем.
class IDialogInitiable {
public:
  // Задать параметры объекта с помощью диалога с пользователем.
  virtual void initFromDialog() = 0;
};

// Интерфейс "Отображаемый"
class IPrintable {
public:
  // Отобразить на экране
  // (выводить в текстовом виде параметры фигуры).
  virtual void draw() = 0;
};

// Вектор
class CVector2D {
public:
  double x, y;
};


class Figure : public IGeoFig, public IDialogInitiable, public IPrintable, public CVector2D{};


class Circle : public Figure {
public:
  int n;
  int mas;
  point center;
  float rad;

  double x = center.x;
  double y = center.y;

  Circle() {
    cout << "New Circle ";
  }

  Circle(float x, float y, float r) {
    center.x = x;
    center.y = y;
    rad = r;
  }

  double square() override {
    return (3.14*rad*rad);
  }
  double perimetr() override {
    return (2*3.14*rad);
  }
  int mass() override {
    return (mas);
  }
  void initFromDialog() override {
    cout << "Enter (x, y) >";
    cin >> center.x >> center.y;
    cout << "Enter radius >";
    cin >> rad;
    cout << "Enter mass >";
    cin >> mas;
  }
  void draw() override {
    cout << "Circle: center (" << center.x << ", " << center.y << ") radius=" << rad << " mass=" << mas << endl;
  }



};

class Parallelogram: public Figure {
public:
  int n;
  int mas;
  point a;
  point b;
  point c;

  double x = a.x + (c.x - a.x)/2;
  double y = a.y + (c.y - a.y)/2;

  Parallelogram () {
    cout << "New Parallelogram ";
  }
  /*
  Parallelogram(point a0, point b0, point c0){
  a = a0;
  b = b0;
  c = c0;
}
*/
double square() override {
  point vec_a = {a.x - b.x, a.y - b.y};
  point vec_c = {c.x - b.x, c.y - b.y};
  float scal = vec_a.x*vec_c.x + vec_a.y*vec_c.y;
  float sin = sqrt(1 - pow(scal/(len(a,b)*len(b,c)),2));
  return (len(a,b)*len(b,c)*sin);
}
double perimetr() override {
  return (2 * (len(a,b)+len(b,c)) );
}
int mass() override {
  return (mas);
}
void initFromDialog() override {
  cout << "Enter 1(x, y) >";
  cin >> a.x >> a.y;
  cout << "Enter 2(x, y) >";
  cin >> b.x >> b.y;
  cout << "Enter 3(x, y) >";
  cin >> c.x >> c.y;
  cout << "Enter mass >";
  cin >> mas;
}
void draw() override {
  cout << "Parallelogram: " << endl;
  cout << "1 point (" << a.x << ", " << a.y << ")" << endl;
  cout << "2 point (" << b.x << ", " << b.y << ")" << endl;
  cout << "3 point (" << c.x << ", " << c.y << ")" << endl;
  cout << "4 point (" << c.x+(a.x - b.x) << ", " << c.y+(a.y - b.y) << ")" << endl;
  cout << " mass=" << mas << endl;
}
};



class System  {
public:
  vector < Figure* > figures;

  void save(Figure* fig) {
    cout << "saved " << endl;
    figures.push_back(fig);
  }

  void show_all() {
    for (size_t i = 0; i < figures.size(); i++) {
      cout << i << ". ";
      figures[i]->draw();
    }
  }

  double sum_sqr() {
    double sum = 0;
    for (size_t i = 0; i < figures.size(); i++) {
      sum += figures[i]->square();
    }
    return (sum);
  }

  double sum_perimetr() {
    double sum = 0;
    for (size_t i = 0; i < figures.size(); i++) {
      sum += figures[i]->perimetr();
    }
    return (sum);
  }

  double memsize() {
    double sum = 0;
    for (size_t i = 0; i < figures.size(); i++) {
      sum += sizeof(figures[i]);
    }
    return (sum);
  }

  point CenterM() {
    point sum1 = {0, 0};
    double  sum2;
    for (size_t i = 0; i < figures.size(); i++) {
      sum1 = {sum1.x + figures[i]->x * figures[i]->mass(), sum1.y + figures[i]->y * figures[i]->mass()};
      sum2 += figures[i]->mass();
    }
    sum1 = {sum1.x/sum2, sum1.y/sum2};
    return (sum1);
  }

  void sorting() {
    vector < pair<int , int> > masvec;
    for (size_t i = 0; i < figures.size(); i++) {
      masvec.push_back(make_pair(figures[i]->mass(), i));
    }
    sort(masvec.begin(), masvec.end());

    for (size_t i = 0; i < figures.size(); i++) {
      figures[masvec[i].second]->draw();
    }
  }


};


int main() {
  System sys;

  cout << "2- Динамическое добавление фигур пользователем. (через консоль)" << endl;
  cout << "3 - Отобразить все фигуры." << endl;
  cout << "4 - Суммарная площадь всех фигур." << endl;
  cout << "5 - Суммарный периметр всех фигур." << endl;
  cout << "6 - Память, занимаемая всеми экземплярами классов." << endl;
  cout << "7 - Сортировка фигур между собой по массе." << endl;

  while (1) {
    int ch;
    cout << ">";
    scanf("%d", &ch);;
    switch (ch) {

      case 2: {
        cout << "Choose 1.Circle, 2.Parallelogram " << endl;
        int j = 0;
        scanf("%d", &j);
        if (  j == 2) {
          Figure* fig = new Parallelogram();
          fig->initFromDialog();
          sys.save(fig);
        } else {
          Figure* fig = new Circle();
          fig->initFromDialog();
          sys.save(fig);
        }
      }
      break;

      case 3: {
        cout << "All figures: " << endl;
        sys.show_all();
      }
      break;

      case 4: {
        cout << "Summary square: " << sys.sum_sqr() << endl;
      }
      break;

      case 5: {
        cout << "Summary perimetr: " << sys.sum_perimetr() << endl;
      }
      break;

      case 6: {
        cout << "Summary memory size: " << sys.memsize() << " byte"<< endl;
      }
      break;

      case 7: {
        cout << "All figures in order: ";
        sys.sorting();
      }
      break;

      case 8: {
        cout << "Center of mass :" << sys.CenterM().x << " " << sys.CenterM().y << endl;
      }
      break;
    }
    cout << "Done" << endl;
  }

  printf("wtf\n" );
  return 0;
}
