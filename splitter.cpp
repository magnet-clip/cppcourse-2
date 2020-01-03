#include "splitter.h"

#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string &s) {
  vector<string> res;
  auto prev = s.begin();
  auto it = find(next(prev), s.end(), ' ');
  res.push_back(string(prev, it));
  while (it != s.end()) {
    prev = next(it);
    it = find(next(prev), s.end(), ' ');
    res.push_back(string(prev, it));
  }
  return res;
}