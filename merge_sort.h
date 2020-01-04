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
  //   cout << "---->> " << endl;
  //   print(range_begin, range_end);
  auto length = distance(range_begin, range_end);
  if (length < 2) {
    return;
  }
  vector<typename RandomIt::value_type> elements(range_begin, range_end);
  auto middle = elements.begin() + length / 2;
  MergeSort(elements.begin(), middle);
  MergeSort(middle, elements.end());

  merge(elements.begin(), middle, middle, elements.end(), range_begin);

  //   vector<typename RandomIt::value_type> elements1(range_begin, middle);
  //   MergeSort(elements1.begin(), elements1.end());
  //   vector<typename RandomIt::value_type> elements2(next(middle), range_end);
  //   MergeSort(elements2.begin(), elements2.end());
  //   merge(elements1.begin(), elements1.end(), elements2.begin(),
  //   elements2.end(),
  //         range_begin);
  //   cout << " result " << endl;
  //   print(range_begin, range_end);
  //   cout << "<<---- " << endl;
}
