#include "test.h"
#include "finder.h"
#include "test_runner.h"

void TestThatTestsAreOk() { AssertEqual(1, 1, "1 === 1"); }
void TestSimpleCase() {
  auto res = FindGreaterElements(set<int>{1, 5, 7, 8}, 5);
  set<int> a;
  a.insert(res.begin(), res.end());
  AssertEqual(a, set<int>{7, 8},
              "7 and 8 are greater than 5, while 1 and 5 aren't");
}

void RunAllTests() {
  TestRunner runner;
  runner.RunTest(TestThatTestsAreOk, "Tests");
  runner.RunTest(TestSimpleCase, "Simple case");
}
