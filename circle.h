#pragma once

#include "figure.h"
#include <string>

class Circle : public Figure {
public:
  Circle(int radius) : _radius(radius) {}
  virtual std::string Name() const override;
  virtual float Area() const override;
  virtual float Perimeter() const override;

private:
  int _radius;
};