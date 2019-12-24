#include "test_runner.h"

void Assert(bool b, const string &hint) { AssertEqual(b, true, hint); }

void TestRunner::a() { cout << "A" << endl; }

TestRunner::~TestRunner() {
  if (fail_count > 0) {
    cerr << fail_count << " unit tests failed. Terminate" << endl;
    exit(1);
  }
}
