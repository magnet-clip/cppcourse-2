#pragma once

#include <memory>
#include <sstream>
#include <string>

class Figure {
public:
  virtual std::string Name() const = 0;
  virtual float Area() const = 0;
  virtual float Perimeter() const = 0;
};

std::shared_ptr<Figure> CreateFigure(std::istringstream &ss);