#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

int main() {
  uint32_t N;
  int64_t sum = 0;
  int64_t average = 0;
  cin >> N;
  vector<int32_t> numbers(N, 0);
  for (auto &item : numbers) {
    cin >> item;
    sum += item;
  }
  average = sum / N;
  // cout << "S = " << sum << "; A = " << average << endl;
  auto K = 0u;
  uint32_t pos = 0;
  vector<int32_t> greaters;
  for (const auto &item : numbers) {
    if (item > average) {
      K++;
      greaters.push_back(pos);
    }
    pos++;
  }
  cout << K << endl;
  for (const auto &item : greaters) {
    cout << item << " ";
  }
  cout << endl;
}