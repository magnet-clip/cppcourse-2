#pragma once

#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "date.h"
#include "fast_map.h"

typedef std::function<bool(Date, std::string)> Predicate;
typedef std::vector<std::pair<Date, std::string>> DbRecord;

class Database {
 public:
  void Add(const Date &date, const std::string &event);
  void Print(const std::ostream &) const;
  bool Last(const Date &date) const;
  int RemoveIf(Predicate predicate);
  DbRecord FindIf(Predicate predicate) const;

 private:
  std::map<Date, FastMap> data;
};