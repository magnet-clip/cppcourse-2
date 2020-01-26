#pragma once

#include <set>
#include <string>
#include <vector>
#include "date.h"

class FastMap {
 public:
  void add(const std::string& event);
  std::string last() const;
  std::vector<std::string> getSequentialItems() const;
  void remove(std::set<std::string> records);

 private:
  std::vector<std::string> _ordered_items;
  std::set<std::string> _fast_access_items;
};
