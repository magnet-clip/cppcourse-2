#pragma once

#include "date.h"
#include <functional>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef std::function<bool(Date, std::string)> Predicate;
typedef std::map<Date,
                 std::pair<std::set<std::string>, std::vector<std::string>>>
    Db;

class Database {
public:
  void Add(const Date &date, const std::string &event);
  void Print(std::ostream &) const;
  std::string Last(const Date &date) const;
  int RemoveIf(Predicate predicate);
  std::vector<std::string> FindIf(Predicate predicate) const;

private:
  std::map<Date, std::set<std::string>> _set;
  std::map<Date, std::vector<std::string>> _vector;
};

void TestDatabase();
void TestRustam();
void TestEmptyNode();
void TestDbAdd();
void TestDbFind();
void TestDbLast();
void TestDbRemoveIf();
void TestInsertionOrder();
void TestsMyCustom();
void TestDatabase2();
