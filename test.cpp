#include "test.h"
#include "builder.h"
#include "test_runner.h"

void TestThatTestsAreOk() { AssertEqual(1, 1, "1 === 1"); }
void TestSimpleBuilder() {
  ExpressionBuilder builder{0, {}};
  AssertEqual(builder.build(), "0", "Zero");
}

void RunAllTests() {
  TestRunner runner;
  runner.RunTest(TestThatTestsAreOk, "Tests");
  runner.RunTest(TestSimpleBuilder, "No operations");
}
