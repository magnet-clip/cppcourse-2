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

void TestIncorrectCases() {
  {
    auto failed = false;
    try {
      PhoneNumber number{"1-2-333"};
    } catch (invalid_argument e) {
      failed = true;
    }

    Assert(failed, "Should have failed 1");
  }

  {
    auto failed = false;
    try {
      PhoneNumber number{"+7-2333"};
    } catch (invalid_argument e) {
      failed = true;
    }

    Assert(failed, "Should have failed 2");
  }
}

void RunAllTests() {
  TestRunner runner;
  runner.RunTest(TestSimple, "Simple test");
  runner.RunTest(TestIncorrectCases, "Incorrect cases");
}

int main() { RunAllTests(); }