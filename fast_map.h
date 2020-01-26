#pragma once

#include <set>
#include <string>
#include <vector>

class FastMap {
 private:
  std::vector<std::string> _ordered_items;
  std::set<std::string> _fast_access_items;
};
