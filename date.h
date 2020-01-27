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
  // Date(const std::string &str);
  int GetYear() const { return year; }
  int GetMonth() const { return month; }
  int GetDay() const { return day; }

private:
  int year, month, day;
};

bool operator<(const Date &lhs, const Date &rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator>(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);
bool operator==(const Date &lhs, const Date &rhs);
bool operator!=(const Date &lhs, const Date &rhs);

std::ostream &operator<<(std::ostream &stream, const Date &date);

Date ParseDate(std::istream &stream);