#include "phone_number.h"

#include <sstream>
using namespace std;

PhoneNumber::PhoneNumber(const string &international_number) {
  /* Принимает строку в формате +XXX-YYY-ZZZZZZ
     Часть от '+' до первого '-' - это код страны.
     Часть между первым и вторым символами '-' - код города
     Всё, что идёт после второго символа '-' - местный номер.
     Код страны, код города и местный номер не должны быть пустыми.
     Если строка не соответствует этому формату, нужно выбросить исключение
     invalid_argument. Проверять, что номер содержит только цифры, не нужно.

     Примеры:
     * +7-495-111-22-33
     * +7-495-1112233
     * +323-22-460002
     * +1-2-coursera-cpp
     * 1-2-333 - некорректный номер - не начинается на '+'
     * +7-1233 - некорректный номер - есть только код страны и города
  */
  stringstream input(international_number);

  char plus, m1, m2;
  int country, city;
  string local;

  input >> plus >> country >> m1 >> city >> m2 >> local;
  if (input.bad() || !input.eof()) {
    throw new invalid_argument("Failed to parse phone number");
  }
  if (plus != '+') {
    throw new invalid_argument("Phone should start with a + sign");
  }
  if (m1 != '-' || m2 != '-') {
    throw new invalid_argument("Delimiters should be -");
  }

  this->country_code_ = to_string(country);
  this->city_code_ = to_string(city);
  this->local_number_ = local;
}

string PhoneNumber::GetCountryCode() const { return this->country_code_; }

string PhoneNumber::GetCityCode() const { return this->city_code_; }

string PhoneNumber::GetLocalNumber() const { return this->local_number_; }

string PhoneNumber::GetInternationalNumber() const {
  stringstream res;
  res << '+' << this->country_code_ << '-' << this->city_code_ << '-'
      << this->local_number_;
  return res.str();
}