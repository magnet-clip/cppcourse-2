#include "circle.h"

using namespace std;

const float PI = 3.14;

inline std::string Circle::Name() const { return "CIRCLE"; }

inline float Circle::Area() const { return PI * this->_radius * this->_radius; }

inline float Circle::Perimeter() const { return 2 * PI * this->_radius; }