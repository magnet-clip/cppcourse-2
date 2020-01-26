#include "database.h"
using namespace std;

void Database::Add(const Date &date, const std::string &event) {
  _data[date].add(event);
}

void Database::Print(std::ostream &ss) const {
  for (auto it = _data.begin(); it != _data.end(); it++) {
    auto &[date, events] = *it;
    for (const auto &event : events.getSequentialItems()) {
      ss << date << " " << event;
    }
  }
}

DbRecord Database::Last(const Date &date) const {
  FastMap item;
  auto actual_date = date;
  if (_data.count(date)) {
    item = _data.at(date);
  } else {
    auto position = _data.lower_bound(date);
    if (position != _data.begin()) {
      tie(actual_date, item) = *prev(position);
    } else {
      throw invalid_argument("No entries");
    }
  }

  return make_pair(actual_date, item.last());
}

int Database::RemoveIf(Predicate predicate) {
  int count;
  for (auto it = _data.begin(); it != _data.end(); it++) {
    auto &[date, events] = *it;
    set<string> events_to_delete;
    for (const auto &event : events.getSequentialItems()) {
      if (predicate(date, event)) {
        events_to_delete.insert(event);
      }
    }
    events.remove(events_to_delete);
    count += events_to_delete.size();
  }
  return count;
}

DbRecords Database::FindIf(Predicate predicate) const {
  DbRecords res;
  for (auto it = _data.begin(); it != _data.end(); it++) {
    auto &[date, events] = *it;
    for (const auto &event : events.getSequentialItems()) {
      if (predicate(date, event)) {
        res.push_back(make_pair(date, event));
      }
    }
  }
  return res;
}