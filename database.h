#pragma once

#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "date.h"

typedef std::function<bool(Date, std::string)> Predicate;
class Database {
 public:
  void Add(const Date &date, const std::string &event);
  void Find(const Date &date) const;
  void Print(const std::ostream &) const;
  bool Last(const Date &date) const;
  int RemoveIf(Predicate predicate);
  std::vector<std::pair<Date, std::string>> FindIf(Predicate predicate) const;

 private:
  std::map<Date, std::vector<std::string>> data;
};