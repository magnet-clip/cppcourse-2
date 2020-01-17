#include "figure.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

#include <memory>
#include <sstream>
#include <string>

using namespace std;

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