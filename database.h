#pragma once

#include <sstream>
#include <string>
#include <vector>
#include "date.h"

class Database {
 public:
  void Add(const Date &date, const std::string &event) {}
  void Find(const Date &date) const {}
  void Print(const std::ostream &ss) const {}
  bool Last(const Date &date) const {}
  template <class Predicate>
  int RemoveIf(Predicate p) const {
    return 0;
  }

  // TODO what return type, vector of what?
  template <class Predicate>
  std::vector<std::pair<Date, std::string>> FindIf(Predicate p) const {
    return std::vector<std::pair<Date, std::string>>{};
  }
};