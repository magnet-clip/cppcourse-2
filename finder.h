#pragma once

#include <algorithm>
#include <cstring>
#include <iostream>
#include <utility>
using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin,
                                        RandomIt range_end, char prefix) {
  string s;
  s = prefix;
  return make_pair(
      lower_bound(range_begin, range_end, s),
      upper_bound(range_begin, range_end, s,
                  [](auto &v1, auto &v2) { return (v1[0] < v2[0]); }));
}

template <typename RandomIt>
pair<RandomIt, RandomIt>
FindStartsWith(RandomIt range_begin, RandomIt range_end, const string &prefix) {
  string s;
  s = prefix;
  return make_pair(
      lower_bound(range_begin, range_end, s),
      upper_bound(range_begin, range_end, s, [&prefix](auto &s1, auto &s2) {
        if (auto cmp = strncmp(s1.data(), s2.data(), prefix.size()))
          return cmp < 0;

        return false;
      }));
}