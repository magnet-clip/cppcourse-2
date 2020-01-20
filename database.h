#pragma once

#include "date.h"
#include <sstream>
#include <string>
#include <vector>

class Database {
public:
  void Add(const Date &date, const std::string &event);
  void Find(const Date &date) const;
  void Print(const std::ostream &ss) const;
  bool Last(const Date &date) const;
  template <class Predicate> int RemoveIf(Predicate p) const {}
  template <class Predicate> std::vector<bool> FindIf(Predicate p) const {}
};