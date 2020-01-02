#pragma once
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T> &elements, const T &border) {
  vector<T> res;

  auto predicate = [&border](auto &item) { return item > border; };
  auto it = find_if(elements.begin(), elements.end(), predicate);
  while (it != elements.end()) {
    res.push_back(*it);
    it = find_if(next(it), elements.end(), predicate);
  }
  //   sort(res);
  return res;
}