#include "fast_map.h"
#include <algorithm>

using namespace std;

void FastMap::add(const string &event) {
  if (!_fast_access_items.count(event)) {
    _ordered_items.push_back(event);
    _fast_access_items.insert(event);
  }
}

vector<string> FastMap::getSequentialItems() const { return _ordered_items; }

string FastMap::last() const { return _ordered_items.back(); }

void FastMap::remove(set<string> records) {
  for (const auto &item : records) {
    _fast_access_items.erase(item);
  }
  const auto &new_start = stable_partition(
      _ordered_items.begin(), _ordered_items.end(),
      [&records](string &item) { return records.count(item); });
  _ordered_items.erase(_ordered_items.begin(), new_start);
}
