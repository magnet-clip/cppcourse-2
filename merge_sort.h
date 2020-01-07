#pragma once
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

// template <typename RandomIt>
// void print(RandomIt range_begin, RandomIt range_end) {
//   do {
//     cout << *range_begin++;
//   } while (range_begin != range_end);
//   cout << endl;
// }

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  auto length = distance(range_begin, range_end);
  if (length < 2) {
    return;
  }
  vector<typename RandomIt::value_type> elements(range_begin, range_end);
  auto p1 = elements.begin() + length / 3;
  MergeSort(elements.begin(), p1);
  auto p2 = p1 + length / 3;
  MergeSort(p1, p2);
  MergeSort(p2, elements.end());
  vector<typename RandomIt::value_type> temp;
  merge(elements.begin(), p1, p1, p2, back_inserter(temp));
  merge(temp.begin(), temp.end(), p2, elements.end(), range_begin);
}
