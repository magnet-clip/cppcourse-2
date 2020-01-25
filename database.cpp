#include "database.h"
using namespace std;

void Database::Add(const Date &date, const std::string &event) {}

void Database::Find(const Date &date) const {}

void Database::Print(const std::ostream &ss) const {}

bool Database::Last(const Date &date) const {}

int Database::RemoveIf(Predicate predicate) {}
vector<pair<Date, string>> Database::FindIf(Predicate predicate) const {
  return vector<pair<Date, string>>{};
}