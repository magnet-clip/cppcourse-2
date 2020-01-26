#pragma once

#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "date.h"
#include "fast_map.h"

typedef std::function<bool(Date, std::string)> Predicate;
typedef std::pair<Date, std::string> DbRecord;
typedef std::vector<DbRecord> DbRecords;

class Database {
 public:
  void Add(const Date &date, const std::string &event);
  void Print(std::ostream &) const;
  DbRecord Last(const Date &date) const;
  int RemoveIf(Predicate predicate);
  DbRecords FindIf(Predicate predicate) const;

 private:
  std::map<Date, FastMap> _data;
};