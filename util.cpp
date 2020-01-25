#include "util.h"
#include "date.h"

using namespace std;

ostream &operator<<(ostream &stream, const pair<Date, string> &item) {
  const auto &[date, str] = item;
  return stream << date << " " << str;
}