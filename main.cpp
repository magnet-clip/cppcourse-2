#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

#pragma region TEST
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
#pragma endregion

#define LOCAL

#ifdef LOCAL
class Rational {
public:
  Rational() {
    num = 0;
    denom = 1;
  }

  Rational(int numerator, int denominator) {

    if (denominator == 0) {
      throw invalid_argument("denominator is 0");
    }

    if (numerator == 0) {
      num = 0;
      denom = 1;
    } else {
      auto divisor = gcd(abs(numerator), abs(denominator));
      num = numerator / divisor;
      denom = denominator / divisor;
    }

    if (denom < 0) {
      num = -num;
      denom = -denom;
    }
  }

  int Numerator() const { return num; }

  int Denominator() const { return denom; }

private:
  int num, denom;

  int gcd(int n1, int n2) {
    auto smallest = min(n1, n2);
    auto largest = max(n1, n2);

    if (smallest == 0 || smallest == 1) {
      return 1;
    }

    while (smallest != 0) {
      auto m = largest % smallest;
      largest = smallest;
      smallest = m;
    }
    return largest;
  }
};

Rational operator+(const Rational &a, const Rational &b) {
  return Rational(a.Numerator() * b.Denominator() +
                      b.Numerator() * a.Denominator(),
                  a.Denominator() * b.Denominator());
}

Rational operator-(const Rational &a, const Rational &b) {
  return Rational(a.Numerator() * b.Denominator() -
                      b.Numerator() * a.Denominator(),
                  a.Denominator() * b.Denominator());
}

Rational operator*(const Rational &a, const Rational &b) {
  return Rational(a.Numerator() * b.Numerator(),
                  a.Denominator() * b.Denominator());
}

Rational operator/(const Rational &a, const Rational &b) {
  if (b.Numerator() == 0) {
    throw domain_error("Division by zero");
  }
  return Rational(a.Numerator() * b.Denominator(),
                  a.Denominator() * b.Numerator());
}

bool operator==(const Rational &a, const Rational &b) {
  return a.Numerator() == b.Numerator() && a.Denominator() == b.Denominator();
}

bool operator!=(const Rational &a, const Rational &b) { return !(a == b); }

bool operator<(const Rational &a, const Rational &b) {
  return a.Numerator() * b.Denominator() < a.Denominator() * b.Numerator();
}

ostream &operator<<(ostream &stream, const Rational &a) {
  stream << a.Numerator() << "/" << a.Denominator();
  return stream;
}

#endif

void TestDefaultConstructor() {
  Rational a;
  AssertEqual(a.Numerator(), 0, "0");
  AssertEqual(a.Denominator(), 1, "1");
}

void TestGcd() {
  Rational a(4, 6);
  AssertEqual(a.Numerator(), 2, "a");
  AssertEqual(a.Denominator(), 3, "b");
  AssertEqual(a, Rational(2, 3), "c");

  Rational b(1, 3);
  AssertEqual(b.Numerator(), 1, "d");
  AssertEqual(b.Denominator(), 3, "e");

  AssertEqual(Rational(4, 6), Rational(2, 3), "f");
  AssertEqual(Rational(17, 6), Rational(17, 6), "g");
  AssertEqual(Rational(22, 22), Rational(1, 1), "h");
}

void TestNegativeRational() {
  AssertEqual(Rational(-1, 22), Rational(-1, 22));
  AssertEqual(Rational(1, -100), Rational(-1, 100));
  AssertEqual(Rational(-1, 1), Rational(-1, 1));
  AssertEqual(Rational(1, -1), Rational(-1, 1));
}

void TestPositiveRational() {
  AssertEqual(Rational(-1, -22), Rational(1, 22));
  AssertEqual(Rational(-1, -100), Rational(1, 100));
  AssertEqual(Rational(-3, -100), Rational(3, 100));
}

void TestZeroNumerator() {
  AssertEqual(Rational(0, 22), Rational(0, 1));
  AssertEqual(Rational(0, -100), Rational(0, 1));
}

int main() {
  TestRunner runner;
  // 1. Конструктор по умолчанию должен создавать дробь с числителем 0 и
  // знаменателем 1.
  runner.RunTest(TestDefaultConstructor, "Default Constructor");

  // 2. При конструировании объекта класса Rational с параметрами p и q должно
  // выполняться сокращение дроби p/q.
  runner.RunTest(TestGcd, "Greatest Common Divisor");

  // 3. Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь
  // отрицательный числитель и положительный знаменатель.
  runner.RunTest(TestNegativeRational, "Negatives");

  // 4. Если дробь p/q положительная, то объект Rational(p, q) должен иметь
  // положительные числитель и знаменатель (обратите внимание на случай
  // Rational(-2, -3)).
  runner.RunTest(TestPositiveRational, "Positives");

  // 5. Если числитель дроби равен нулю, то знаменатель должен быть равен 1.
  runner.RunTest(TestZeroNumerator, "Zero numerator");

  return 0;
}