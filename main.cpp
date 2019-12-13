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

bool IsPalindrom(const string &str) {
  int pos_start = 0, pos_end = str.length() - 1;
  auto res = true;
  while ((pos_start < pos_end) && res) {
    res &= str[pos_start++] == str[pos_end--];
  }
  return res;
}

void TestEmptyStringIsPalindrom() { Assert(IsPalindrom(""), "Empty"); }

void TestOneLetterStrings() {
  Assert(IsPalindrom("a"), "a");
  Assert(IsPalindrom("b"), "b");
  Assert(IsPalindrom("_"), "_");
  // Assert(IsPalindrom("ф"), "ф");
  Assert(IsPalindrom("1"), "1");
}

void TestTwoLetterStrings() {
  Assert(IsPalindrom("aa"), "aa");
  Assert(IsPalindrom("bb"), "bb");
  Assert(!IsPalindrom("ab"), "ab");
  Assert(!IsPalindrom("ba"), "ba");
  Assert(IsPalindrom("__"), "__");
}

void TestThreeLetterStrings() {
  Assert(IsPalindrom("aaa"), "aaa");
  Assert(IsPalindrom("bab"), "bab");
  Assert(IsPalindrom("aba"), "aba");
  Assert(!IsPalindrom("baa"), "baa");
  Assert(!IsPalindrom("abb"), "abb");
  Assert(IsPalindrom("___"), "___");
}

void TestLongerStrings() {
  Assert(IsPalindrom("aaaa"), "aaaa");
  Assert(IsPalindrom("abba"), "abba");
  Assert(!IsPalindrom("aaba"), "aaba");
  Assert(!IsPalindrom("abaa"), "abaa");
  Assert(!IsPalindrom("aaaA"), "aaaA");
  Assert(IsPalindrom("AaaA"), "AaaA");
  Assert(IsPalindrom("aavaa"), "aavaa");
  Assert(!IsPalindrom("abvaa"), "abvaa");
  Assert(IsPalindrom("madam"), "madam");
  Assert(IsPalindrom("level"), "level");
  Assert(!IsPalindrom("leve1"), "leve1");
  Assert(!IsPalindrom("1evel"), "1evel");
  Assert(IsPalindrom("777777"), "777777");
  Assert(!IsPalindrom("777778"), "777778");
  Assert(!IsPalindrom("XabbaY"), "XabbaY");
  Assert(IsPalindrom("wasitacaroracatisaw"), "wasitacaroracatisaw");
  Assert(!IsPalindrom("madam level"), "madam level");
  Assert(!IsPalindrom("gentleman"), "gentleman ");
  Assert(!IsPalindrom("world"), "world");
  Assert(!IsPalindrom("hello"), "hello");
  Assert(!IsPalindrom("madaM"), "madaM ");
  Assert(!IsPalindrom("Madam"), "Madam");
  Assert(!IsPalindrom("madamworldmadam"), "madamworldmadam");
  Assert(IsPalindrom("madammadam"), "madammadam");
  Assert(IsPalindrom("madammadammadammadam"), "madammadammadammadam");
  Assert(IsPalindrom("madammadammadammadammadammadammadammadam"),
         "madammadammadammadammadammadammadammadam");
}

void TestSpaces() {
  Assert(!IsPalindrom(" madam"), "_madam");
  Assert(!IsPalindrom("madam "), "madam_");
  Assert(!IsPalindrom("madam "), "madam_");
  Assert(!IsPalindrom("Amadam "), "Amadam_");
  Assert(!IsPalindrom("madamA "), "madamA_");
  Assert(IsPalindrom(" madam "), "_madam_");
  Assert(!IsPalindrom("  madam "), "__madam_");
  Assert(IsPalindrom("  madam  "), "__madam__");
  Assert(IsPalindrom("  ma d am  "), "__ma_d_am__");
  Assert(IsPalindrom("  ma   am  "), "__ma___am__");
  Assert(IsPalindrom("  ma     am  "), "__ma_____am__");
  Assert(IsPalindrom("   "), "   ");
  Assert(IsPalindrom("  "), "  ");
  Assert(IsPalindrom(" "), " ");
  Assert(IsPalindrom(" _ "), " _ ");
  Assert(IsPalindrom("^_^"), "^_^");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestEmptyStringIsPalindrom, "TestEmptyStringIsPalindrom");
  runner.RunTest(TestOneLetterStrings, "TestOneLetterStrings");
  runner.RunTest(TestTwoLetterStrings, "TestTwoLetterStrings");
  runner.RunTest(TestThreeLetterStrings, "TestThreeLetterStrings");
  runner.RunTest(TestLongerStrings, "TestLongerStrings");
  runner.RunTest(TestSpaces, "TestSpaces");

  return 0;
}
