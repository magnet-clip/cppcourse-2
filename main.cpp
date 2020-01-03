#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

template <class T> ostream &operator<<(ostream &os, const vector<T> &s) {
  os << "[";
  bool first = true;
  for (const auto &x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "]";
}

int main() {

  {
    vector<int> vec;
    auto vector_begin = begin(vec);
    auto vector_end = end(vec);

    string str;
    auto string_begin = begin(str);
    auto string_end = end(str);

    set<int> s;
    auto set_begin = begin(s);
    auto set_end = end(s);

    { auto res = is_permutation(set_begin, set_end, vector_begin); }
    { auto res = is_permutation(vector_begin, vector_end, vector_begin); }
    { partial_sum(set_begin, set_end, vector_begin); }
    // { auto res = is_heap(set_begin, set_end); } +
    // { auto res = is_permutation(set_begin, set_end, back_inserter(vec)); } +
    // { auto res = next_permutation(set_begin, set_end); } +
    // { partial_sum(vector_begin, vector_end, set_begin); }
    { partial_sum(set_begin, set_end, back_inserter(vec)); }
    { auto res = accumulate(vector_begin, vector_end, 0); }
    { auto res = next_permutation(string_begin, string_end); } // +
    { auto res = is_heap(string_begin, string_end); }
    { auto res = accumulate(set_begin, set_end, 0); }
  }
  {
    set<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto f = [](const int &num) { return num % 2; };

    {
      vector<int> v;
      copy_if(begin(s), end(s), back_inserter(v), f);
      cout << v << endl;
    }
    {
      vector<int> v;
      // auto it = partition(begin(s), end(s), f);
      // copy(it, end(s), back_inserter(v));

      cout << v << endl;
    }
    {
      vector<int> v;
      v.assign(begin(s), end(s));
      auto it = partition(begin(v), end(v), f);
      v.erase(it, end(v));
      cout << v << endl;
    }

    {
      vector<int> v;
      v.assign(begin(s), end(s));
      sort(begin(v), end(v),
           [&f](int lhs, int rhs) { return f(lhs) > f(rhs); });
      auto it = partition_point(begin(v), end(v), f);
      v.erase(begin(v), it);
      cout << v << endl;
    }

    {
      vector<int> v;
      vector<int> garbage;
      partition_copy(begin(s), end(s), back_inserter(v), back_inserter(garbage),
                     f);
      cout << v << endl;
    }

    {
      vector<int> v;
      v.assign(begin(s), end(s));
      auto it = remove_if(begin(v), end(v), f);
      v.erase(it, end(v));
      cout << v << endl;
    }

    {
      vector<int> v;
      v.assign(begin(s), end(s));
      auto it = remove_if(begin(v), end(v), [&f](int x) { return !f(x); });
      v.erase(it, end(v));
      cout << v << endl;
    }

    {
      vector<int> v;
      // auto it = remove_if(begin(s), end(s), [&f](int x) { return !f(x); });
      // copy(it, end(s), back_inserter(v));
      cout << v << endl;
    }

    {
      vector<int> v;
      v.assign(begin(s), end(s));
      sort(begin(v), end(v),
           [&f](int lhs, int rhs) { return f(lhs) > f(rhs); });
      auto it = partition_point(begin(v), end(v), f);
      v.erase(it, end(v));
      cout << v << endl;
    }

    {
      vector<int> v;
      remove_copy_if(begin(s), end(s), back_inserter(v),
                     [&f](int x) { return !f(x); });
      cout << v << endl;
    }
    {
      vector<int> v;
      copy_if(begin(s), end(s), back_inserter(v),
              [&f](int x) { return !f(x); });
      cout << v << endl;
    }
    {
      vector<int> v;
      v.assign(begin(s), end(s));
      auto it = partition(begin(v), end(v), f);
      v.erase(begin(v), it);
      cout << v << endl;
    }
    {
      vector<int> v;
      remove_copy_if(begin(s), end(s), back_inserter(v), f);
      cout << v << endl;
    }
    {
      vector<int> v;
      vector<int> garbage;
      partition_copy(begin(s), end(s), back_inserter(garbage), back_inserter(v),
                     f);

      cout << v << endl;
    }
  }
  return 0;
}