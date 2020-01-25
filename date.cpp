#include "date.h"

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

Date ParseDate(std::istringstream &stream) {
  int day = -1998;
  int year, month;

  char def1, def2;
  stream >> year >> def1 >> month >> def2 >> day;

  if (stream.bad() || !stream.eof() || (def1 != '-') || (def2 != '-') ||
      (day == -1998)) {
    throw date_format_exception("Wrong date format");
  }

  if (month < 1 || month > 12) {
    std::stringstream msg_stream;
    msg_stream << "Month value is invalid: " << month;
    throw date_format_exception(msg_stream.str());
  }

  if (day < 1 || day > 31) {
    std::stringstream msg_stream;
    msg_stream << "Day value is invalid: " << day;
    throw date_format_exception(msg_stream.str());
  }

  return Date(year, month, day);
}
