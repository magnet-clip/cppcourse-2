#pragma once

#include <exception>
#include <sstream>
#include <string>

class date_format_exception : std::exception {
public:
  date_format_exception() : exception() {}
  date_format_exception(std::string msg) : exception(), message(msg) {}
  std::string getMessage() { return message; }

private:
  const std::string message;
};

class Date {
public:
  Date() : year(0), month(0), day(0) {}
  Date(int year, int month, int day) : year(year), month(month), day(day) {}
  Date(const std::string &str) {
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
  int GetYear() const { return year; }
  int GetMonth() const { return month; }
  int GetDay() const { return day; }

private:
  int year, month, day;
};

bool operator<(const Date &lhs, const Date &rhs);

Date ParseDate(const std::istringstream &stream);