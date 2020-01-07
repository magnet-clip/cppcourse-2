#include "test.h"
#include "merge_sort.h"
#include "test_runner.h"

void TestThatTestsAreOk() { AssertEqual(1, 1, "1 === 1"); }

void TestSomeSort() {
  vector<int> array = {1, 6, 3, 5, 2, 7, 4, 8, 9};
  MergeSort(array.begin(), array.end());
  AssertEqual(array, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}, "!");
}

void RunAllTests() {
  TestRunner runner;
  runner.RunTest(TestThatTestsAreOk, "Tests");
  runner.RunTest(TestSomeSort, "Sort");
}
