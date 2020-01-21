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

Date::Date(const string &str) {
  // cout << "[" << str << "]" << endl;
  std::stringstream date_stream(str);

  day = -1998;

  char def1, def2;
  date_stream >> year >> def1 >> month >> def2 >> day;

  if (date_stream.bad() || !date_stream.eof() || (def1 != '-') ||
      (def2 != '-') || (day == -1998)) {
    std::stringstream msg_stream;
    msg_stream << "Wrong date format: " << str;
    throw date_format_exception(msg_stream.str());
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
}