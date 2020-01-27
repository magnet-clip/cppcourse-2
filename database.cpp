#include "database.h"
using namespace std;

void Database::Add(const Date &date, const std::string &event) {
  _data[date].add(event);
}

void Database::Print(std::ostream &ss) const {
  for (auto it = _data.begin(); it != _data.end(); it++) {
    auto &[date, events] = *it;
    for (const auto &event : events.getSequentialItems()) {
      ss << date << " " << event << endl;
    }
  }
}

string Database::Last(const Date &date) const {
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

  ostringstream res;
  res << actual_date << " " << item.last();

  return res.str();
}

int Database::RemoveIf(Predicate predicate) {
  int count = 0;
  set<Date> dates_to_remove;
  for (auto it = _data.begin(); it != _data.end(); it++) {
    auto &[date, events] = *it;
    set<string> events_to_delete;
    const auto &items = events.getSequentialItems();
    for (const auto &event : items) {
      if (predicate(date, event)) {
        events_to_delete.insert(event);
      }
    }

    if (events_to_delete.size() == items.size()) {
      dates_to_remove.insert(date);
    } else {
      events.remove(events_to_delete);
    }
    count += events_to_delete.size();
  }
  for (const auto &date : dates_to_remove) {
    _data.erase(date);
  }
  return count;
}

vector<string> Database::FindIf(Predicate predicate) const {
  vector<string> res;
  for (auto it = _data.begin(); it != _data.end(); it++) {
    auto &[date, events] = *it;
    for (const auto &event : events.getSequentialItems()) {
      if (predicate(date, event)) {
        ostringstream item;
        item << date << " " << event;
        res.push_back(item.str());
      }
    }
  }
  return res;
}