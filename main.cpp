#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

template <typename TKey, typename TValue>
TValue &GetRefStrict(map<TKey, TValue> &param, const TKey &key) {
  if (param.count(key)) {
    return param[key];
  } else {
    throw runtime_error("");
  }
}

int main() {
  map<int, string> m = {{0, "value"}};
  string &item = GetRefStrict(m, 0);
  item = "newvalue";
  cout << m[0] << endl; // выведет newvalue
}