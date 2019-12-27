#include "test_runner.h"

void TestRunner::a() { cout << "A" << endl; }

TestRunner::~TestRunner() {
  if (fail_count > 0) {
    cerr << fail_count << " unit tests failed. Terminate" << endl;
    exit(1);
  }
}
