#include "database.h"
using namespace std;

void Database::Add(const Date &date, const std::string &event) {
  auto &set = _set[date];
  auto &vector = _vector[date];
  if (!set.count(event)) {
    vector.push_back(event);
    set.insert(event);
  }
}

void Database::Print(std::ostream &ss) const {
  for (auto it = _vector.begin(); it != _vector.end(); it++) {
    const auto &[date, events] = *it;
    for (const auto &event : events) {
      ss << date << " " << event << endl;
    }
  }
}

string Database::Last(const Date &date) const {
  Date actual_date;
  string record;

  if (_vector.count(date)) {
    actual_date = date;
    record = _vector.at(date).back();
  } else {
    auto position = _vector.lower_bound(date);
    if (position != _vector.begin()) {
      --position;
      actual_date = position->first;
      record = position->second.back();
    } else {
      throw invalid_argument("No entries");
    }
  }

  ostringstream res;
  res << actual_date << " " << record;

  return res.str();
}

int Database::RemoveIf(Predicate predicate) {
  int count = 0;
  set<Date> dates_to_remove;

  // Removing from set
  for (auto &item : _set) {
    const auto &date = item.first;

    const auto pred = [&date, &predicate](const auto &str) {
      return !predicate(date, str);
    };

    set<string> new_events;
    const auto &events = item.second;
    const auto old_size = events.size();
    copy_if(events.begin(), events.end(),
            inserter(new_events, new_events.begin()), pred);
    item.second = new_events;

    // I can now skip vector items for which dates should be removed completely
    if (!new_events.size()) {
      dates_to_remove.insert(date);
    }

    // Is count correct?
    count += old_size - new_events.size();
  }

  // Removing from vector
  for (auto &item : _vector) {
    const auto &date = item.first;
    auto &events = item.second;

    // Day will be removed completely
    if (dates_to_remove.count(date)) {
      continue;
    }

    const auto pred = [date, predicate](const auto &str) {
      return predicate(date, str);
    };

    const auto &new_start =
        stable_partition(events.begin(), events.end(), pred);
    events.erase(events.begin(), new_start);
  }

  // Cleaning up empty dates
  for (const auto &date : dates_to_remove) {
    _set.erase(date);
    _vector.erase(date);
  }

  return count;
}

vector<string> Database::FindIf(Predicate predicate) const {
  vector<string> res;

  for (auto it = _vector.begin(); it != _vector.end(); it++) {
    auto date = it->first;
    const auto &items = it->second;
    auto items_it = items.begin();
    do {
      items_it =
          find_if(items_it, items.end(), [date, predicate](const string &str) {
            return predicate(date, str);
          });

      if (items_it == items.end()) {
        break;
      }

      ostringstream item;
      item << date << " " << *items_it;
      res.push_back(item.str());

      items_it++;
    } while (items_it != items.end());
  }
  return res;
}

/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
18-19 тесты проверяют работу методов RemoveIf и Last.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Для Find_If - find_if c полученными предикатом
~~~~~~~~~~~~~~~~~~~~~~~~~~
ну и в цикле for это делается без особых затрат. Главное понимать, что метод
erase возвращает следующий после удаляемого итератор. Поэтому варианты удаления
в цикле могут быть следующие:

std::set<int> sets{/////};
// pred - ~ bool
for(auto it = begin(sets);it!=end(sets);){
  if(pred(*it)) it=sets.erase(it);
  else ++it;
}

или
for(auto it = begin(sets);it!=end(sets);){
  if(pred(*it)) sets.erase(it++);
  else ++it;
}

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
У Вас все очень похоже на правду. Единственное то, что Вы сами усложняете себе
жизнь. В Last более чем достаточно upper_bound - и в случае успеха вернуть
соотв. элемент ( три - четыре строчки на весь метод Last). При добавлении
элементов - посмотрите возвращаемое значение методом insert в std::set на
cppreference - это позволит Вам избежать лишних проверок. И попробуйте немного
перестроить Remove_if - после сортировки в векторе циклом по отсортированному
диапазону удалите сначала все из сета, а потом сам вектор почистите. Возможно
данные упрощения Вашего кода помогут пройти тесты.

UPD: После долгих мучений
все-таки сдал, воспользовался подсказками, которые оставили ниже. Переделал
RemoveIf: очищал весь set и заново заполнял нужными данными. Добавлял пустые
даты в другой вектор и уже по нему проходился в цикле и очищал вектор и сет,
чтобы избежать прохождения циклом по контейнеру и удалению из него. Всем удачи,
главное не сдавайтесь!
*/
