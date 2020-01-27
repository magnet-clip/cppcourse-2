#include "date.h"
#include <iomanip>

using namespace std;

bool operator<(const Date &lhs, const Date &rhs) {
  if (lhs.GetYear() == rhs.GetYear()) {
    if (lhs.GetMonth() == rhs.GetMonth()) {
      return lhs.GetDay() < rhs.GetDay();
    } else {
      return lhs.GetMonth() < rhs.GetMonth();
    }
  } else {
    return lhs.GetYear() < rhs.GetYear();
  }
}

bool operator>(const Date &lhs, const Date &rhs) {
  if (lhs.GetYear() == rhs.GetYear()) {
    if (lhs.GetMonth() == rhs.GetMonth()) {
      return lhs.GetDay() > rhs.GetDay();
    } else {
      return lhs.GetMonth() > rhs.GetMonth();
    }
  } else {
    return lhs.GetYear() > rhs.GetYear();
  }
}

bool operator==(const Date &lhs, const Date &rhs) {
  return (lhs.GetYear() == rhs.GetYear()) &&
         (lhs.GetMonth() == rhs.GetMonth()) && (lhs.GetDay() == rhs.GetDay());
}

bool operator!=(const Date &lhs, const Date &rhs) { return !(lhs == rhs); }

bool operator>=(const Date &lhs, const Date &rhs) {
  return (lhs == rhs) || (lhs > rhs);
}
bool operator<=(const Date &lhs, const Date &rhs) {
  return (lhs == rhs) || (lhs < rhs);
}

Date ParseDate(std::istream &stream) {
  int day = -1998;
  int year, month;

  char def1, def2;
  stream >> year >> def1 >> month >> def2 >> day;

  return Date(year, month, day);
}

ostream &operator<<(ostream &stream, const Date &date) {
  stream << setw(4) << setfill('0') << date.GetYear();
  stream << "-";
  stream << setw(2) << setfill('0') << date.GetMonth();
  stream << "-";
  stream << setw(2) << setfill('0') << date.GetDay();
  return stream;
}
