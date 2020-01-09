#include "test.h"
#include "finder.h"
#include "test_runner.h"

void TestThatTestsAreOk() { AssertEqual(1, 1, "1 === 1"); }

void TestFinderEmpty() {
  vector<string> empty{};
  auto res = FindStartsWith(empty.begin(), empty.end(), 'A');
  AssertEqual((res.first - empty.begin()), 0, "start");
  AssertEqual((res.second - empty.begin()), 0, "end");
}

void TestFinderSimple() {
  vector<string> simple{"a", "a", "b", "b", "c", "c"};
  auto res = FindStartsWith(simple.cbegin(), simple.cend(), 'b');
  AssertEqual((res.first - simple.begin()), 2, "start");
  AssertEqual((res.second - simple.begin()), 4, "end");
}

void TestFinderSimple2() {
  vector<string> simple{"alpha", "beta", "buter", "corn"};
  auto res = FindStartsWith(simple.begin(), simple.end(), 'b');
  AssertEqual((res.first - simple.begin()), 1, "start");
  AssertEqual((res.second - simple.begin()), 3, "end");
}

void TestFinderSimple3() {
  vector<string> simple{"alpha", "beta", "buter", "corn"};
  auto res = FindStartsWith(simple.begin(), simple.end(), 'c');
  AssertEqual((res.first - simple.begin()), 3, "start");
  AssertEqual((res.second - simple.begin()), 4, "end");
}

void TestFinderAdvanced() {
  vector<string> simple{"alpha", "beta", "buter", "corn"};
  auto res = FindStartsWith(simple.begin(), simple.end(), "be");
  AssertEqual((res.first - simple.begin()), 1, "start");
  AssertEqual((res.second - simple.begin()), 2, "end");
}
void TestFinderAdvanced2() {
  vector<string> simple{"alpha", "beta", "belka", "buter", "corn"};
  auto res = FindStartsWith(simple.begin(), simple.end(), "be");
  AssertEqual((res.first - simple.begin()), 1, "start");
  AssertEqual((res.second - simple.begin()), 3, "end");
}

void RunAllTests() {
  TestRunner runner;
  runner.RunTest(TestThatTestsAreOk, "Tests");
  runner.RunTest(TestFinderEmpty, "Empty finder");
  runner.RunTest(TestFinderSimple, "Simple finder");
  runner.RunTest(TestFinderSimple2, "Simple 2 finder");
  runner.RunTest(TestFinderSimple3, "Simple 3 finder");
  runner.RunTest(TestFinderAdvanced, "Adv finder");
  runner.RunTest(TestFinderAdvanced2, "Adv 2 finder");
}
