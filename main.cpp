#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

template <typename T> T Sqr(const T &param) { return param * param; }

template <typename T> vector<T> Sqr(const vector<T> &param) {
  vector<T> res;
  for (const auto &item : param) {
    res.push_back(item * item);
  }
  return res;
}

template <typename T, typename U> map<T, U> Sqr(const map<T, U> &param) {
  map<T, U> res;
  for (const auto &item : param) {
    res[item.first] = item.second * item.second;
  }
  return res;
}

int main() {
  // Пример вызова функции
  vector<int> v = {1, 2, 3};
  cout << "vector:";
  for (int x : Sqr(v)) {
    cout << ' ' << x;
  }
  cout << endl;

  map<int, pair<int, int>> map_of_pairs = {{4, {2, 2}}, {7, {4, 3}}};
  cout << "map of pairs:" << endl;
  for (const auto &x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }
}