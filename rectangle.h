#pragma once

#include "figure.h"
#include <string>

class Rectangle : public Figure {
public:
  Rectangle(int width, int height) : _widht(width), _height(height) {}
  virtual std::string Name() const override;
  virtual float Area() const override;
  virtual float Perimeter() const override;

private:
  int _widht, _height;
};