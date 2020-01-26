#include "database.h"
using namespace std;

void Database::Add(const Date &date, const std::string &event) {}

void Database::Print(const std::ostream &ss) const {}

bool Database::Last(const Date &date) const {}

int Database::RemoveIf(Predicate predicate) {}

DbRecord Database::FindIf(Predicate predicate) const { return DbRecord{}; }