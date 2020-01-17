#include <iomanip>
#include <iostream>
#include <math.h>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Figure {
public:
  virtual string Name() const = 0;
  virtual float Area() const = 0;
  virtual float Perimeter() const = 0;
};

class Rectangle : public Figure {
public:
  Rectangle(int width, int height) : _width(width), _height(height) {}
  virtual string Name() const override;
  virtual float Area() const override;
  virtual float Perimeter() const override;

private:
  int _width, _height;
};

class Circle : public Figure {
public:
  Circle(int radius) : _radius(radius) {}
  virtual string Name() const override;
  virtual float Area() const override;
  virtual float Perimeter() const override;

private:
  int _radius;
};

class Triangle : public Figure {
public:
  Triangle(int a, int b, int c) : _a(a), _b(b), _c(c) {}
  virtual string Name() const override;
  virtual float Area() const override;
  virtual float Perimeter() const override;

private:
  int _a, _b, _c;
};

shared_ptr<Figure> CreateFigure(istringstream &ss) {
  string kind;
  ss >> kind;
  if (kind == "RECT") {
    int width, height;
    ss >> width >> height;
    return make_shared<Rectangle>(width, height);
  } else if (kind == "TRIANGLE") {
    int a, b, c;
    ss >> a >> b >> c;
    return make_shared<Triangle>(a, b, c);
  } else if (kind == "CIRCLE") {
    int r;
    ss >> r;
    return make_shared<Circle>(r);
  } else {
    return 0;
  }
}

inline string Rectangle::Name() const { return "RECTANGLE"; }

inline float Rectangle::Area() const { return this->_width * this->_height; }

inline float Rectangle::Perimeter() const {
  return 2 * (this->_width + this->_height);
}

inline string Triangle::Name() const { return "TRIANGLE"; }

float Triangle::Area() const {
  float p = (this->_a + this->_b + this->_c) / 2.0f;
  return sqrt(p * (p - this->_a) * (p - this->_b) * (p - this->_c));
}

inline float Triangle::Perimeter() const {
  return this->_a + this->_b + this->_c;
}

const float PI = 3.14;

inline string Circle::Name() const { return "CIRCLE"; }

inline float Circle::Area() const { return PI * this->_radius * this->_radius; }

inline float Circle::Perimeter() const { return 2 * PI * this->_radius; }

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line);) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto &current_figure : figures) {
        cout << fixed << setprecision(3) << current_figure->Name() << " "
             << current_figure->Perimeter() << " " << current_figure->Area()
             << endl;
      }
    }
  }
  return 0;
}