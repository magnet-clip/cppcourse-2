#include "test.h"
#include "test_runner.h"

void TestThatTestsAreOk() { AssertEqual(1, 1, "1 === 1"); }

void RunAllTests() {
  TestRunner runner;
  runner.RunTest(TestThatTestsAreOk, "Tests Are Ok");
}
