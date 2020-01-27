#pragma once

#include "date.h"
#include "fast_map.h"
#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <vector>

typedef std::function<bool(Date, std::string)> Predicate;
typedef std::pair<Date, std::string> DbRecord;
typedef std::vector<DbRecord> DbRecords;

class Database {
public:
  void Add(const Date &date, const std::string &event);
  void Print(std::ostream &) const;
  std::string Last(const Date &date) const;
  int RemoveIf(Predicate predicate);
  std::vector<std::string> FindIf(Predicate predicate) const;

private:
  std::map<Date, FastMap> _data;
};

void TestDatabase();

void TestEmptyNode();
void TestDbAdd();
void TestDbFind();
void TestDbLast();
void TestDbRemoveIf();
void TestInsertionOrder();
void TestsMyCustom();
void TestDatabase2();
