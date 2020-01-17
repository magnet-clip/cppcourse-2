#include "rectangle.h"

using namespace std;

inline std::string Rectangle::Name() const { return "RECTANGLE"; }

inline float Rectangle::Area() const { return this->_widht * this->_height; }

inline float Rectangle::Perimeter() const {
  return 2 * (this->_widht + this->_height);
}