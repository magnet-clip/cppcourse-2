#pragma once
#include "date.h"
#include <string>

class Node {
public:
  bool Evaluate(const Date &date, const std::string &event);
};