#include "phone_number.h"
#include "test_runner.h"
#include <iostream>

using namespace std;

void TestSimple() {
  PhoneNumber number{"+7-916-3222223"};
  AssertEqual(number.GetCityCode(), "916", "city code");
  AssertEqual(number.GetCountryCode(), "7", "country code");
  AssertEqual(number.GetLocalNumber(), "3222223", "local number");
}

void RunAllTests() {
  TestRunner runner;
  runner.RunTest(TestSimple, "Simple test");
}

int main() { RunAllTests(); }