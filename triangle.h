#pragma once

#include "figure.h"
#include <string>

class Triangle : public Figure {
public:
  Triangle(int a, int b, int c) : _a(a), _b(b), _c(c) {}
  virtual std::string Name() const override;
  virtual float Area() const override;
  virtual float Perimeter() const override;

private:
  int _a, _b, _c;
};