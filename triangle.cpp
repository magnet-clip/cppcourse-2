#include "triangle.h"
#include <math.h>

using namespace std;

inline std::string Triangle::Name() const { return "TRIANGLE"; }

float Triangle::Area() const {
  float p = (this->_a + this->_b + this->_c) / 2.0f;
  return sqrt(p * (p - this->_a) * (p - this->_b) * (p - this->_c));
}

inline float Triangle::Perimeter() const {
  return this->_a + this->_b + this->_c;
}