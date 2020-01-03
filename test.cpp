#include "test.h"
#include "splitter.h"
#include "test_runner.h"

void TestThatTestsAreOk() { AssertEqual(1, 1, "1 === 1"); }
void TestSimpleCase() {
  {
    auto res = SplitIntoWords("Hello");
    AssertEqual(res, vector<string>{"Hello"}, "Hello");
  }
  {
    auto res = SplitIntoWords("Hello World");
    AssertEqual(res, vector<string>{"Hello", "World"}, "Hello world");
  }
}

void RunAllTests() {
  TestRunner runner;
  runner.RunTest(TestThatTestsAreOk, "Tests");
  runner.RunTest(TestSimpleCase, "Simple case");
}
