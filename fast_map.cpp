#include "fast_map.h"

using namespace std;

void FastMap::add(const string& event) {
  if (!_fast_access_items.count(event)) {
    _ordered_items.push_back(event);
    _fast_access_items.insert(event);
  }
}

vector<string> FastMap::getSequentialItems() const { return _ordered_items; }

string FastMap::last() const { return _ordered_items.back(); }