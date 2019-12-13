#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T> ostream &operator<<(ostream &os, const vector<T> &s) {
  os << "{";
  bool first = true;
  for (const auto &x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T> ostream &operator<<(ostream &os, const set<T> &s) {
  os << "{";
  bool first = true;
  for (const auto &x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
  os << "{";
  bool first = true;
  for (const auto &kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string &hint) { AssertEqual(b, true, hint); }

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string &test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception &e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c) {
  if (a == 0.0 && b == 0.0 && c != 0.0)
    return 0;

  if (a == 0.0 && b != 0.0)
    return 1;

  auto D = b * b - 4 * a * c;
  if (D > 0) {
    return 2;
  } else if (D < 0) {
    return 0;
  } else {
    return 1;
  }
}

void TestZeroAB() {
  AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0);
  AssertEqual(GetDistinctRealRootCount(0, 0, 10), 0);
  AssertEqual(GetDistinctRealRootCount(0, 0, 100), 0);
  AssertEqual(GetDistinctRealRootCount(0, 0, -1), 0);
  AssertEqual(GetDistinctRealRootCount(0, 0, -1000), 0);
}

void TestZeroANonZeroB() {
  AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1);
  AssertEqual(GetDistinctRealRootCount(0, 1, 10), 1);
  AssertEqual(GetDistinctRealRootCount(0, 10000, 100), 1);
  AssertEqual(GetDistinctRealRootCount(0, -100, -1), 1);
  AssertEqual(GetDistinctRealRootCount(0, 0.1, -1000), 1);
}

void TestOthers() {
  AssertEqual(GetDistinctRealRootCount(1, 3, 1), 2);
  AssertEqual(GetDistinctRealRootCount(1, 2, 1), 1);
  AssertEqual(GetDistinctRealRootCount(1, 1, 1), 0);
}

int main() {
  TestRunner runner;
  runner.RunTest(TestZeroAB, "Zero A and B");
  runner.RunTest(TestZeroANonZeroB, "Zero A and nonzero B");
  runner.RunTest(TestOthers, "Nonzero A");
  return 0;
}