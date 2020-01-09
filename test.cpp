#include "test.h"
#include "builder.h"
#include "test_runner.h"
#include <vector>

void TestThatTestsAreOk() { AssertEqual(1, 1, "1 === 1"); }

void TestSimpleBuilder() {
  ExpressionBuilder builder{0, {}};
  AssertEqual(builder.build(), "0", "Zero");
}

void TestOneStepBuilder() {
  {
    ExpressionBuilder builder{0, {{OperationType::add, 1}}};
    AssertEqual(builder.build(), "0 + 1", "One");
  }
  {
    ExpressionBuilder builder{0, {{OperationType::sub, 1}}};
    AssertEqual(builder.build(), "0 - 1", "Mul Zero");
  }
  {
    ExpressionBuilder builder{0, {{OperationType::div, 1}}};
    AssertEqual(builder.build(), "0 / 1", "Div Zero");
  }
  {
    ExpressionBuilder builder{0, {{OperationType::mul, 1}}};
    AssertEqual(builder.build(), "0 * 1", "Mul Zero");
  }
}

void TestSeveralStepsBuilder() {
  {
    ExpressionBuilder builder{
        2, {{OperationType::add, 1}, {OperationType::add, -3}}};
    AssertEqual(builder.build(), "2 + 1 + -3", "Complex 1");
  }
  {
    ExpressionBuilder builder{
        2, {{OperationType::mul, 1}, {OperationType::add, -3}}};
    AssertEqual(builder.build(), "2 * 1 + -3", "Complex 2");
  }
  {
    ExpressionBuilder builder{
        2, {{OperationType::add, 1}, {OperationType::mul, -3}}};
    AssertEqual(builder.build(), "(2 + 1) * -3", "Complex 3");
  }
}

void RunAllTests() {
  TestRunner runner;
  runner.RunTest(TestThatTestsAreOk, "Tests");
  runner.RunTest(TestSimpleBuilder, "No operations");
  runner.RunTest(TestOneStepBuilder, "One operation");
  runner.RunTest(TestSeveralStepsBuilder, "More operations");
}
