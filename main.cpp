#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

#define TEST

#ifdef TEST
stringstream ss;
#define ECHO(str) (ss << (str) << endl)
#define FLUSH() ss.clear();
#else
#define ECHO(str) (cout << (str) << endl)
#endif

class date_format_exception : exception {
public:
  date_format_exception() : exception() {}
  date_format_exception(string msg) : exception(), message(msg) {}
  string getMessage() { return message; }

private:
  string message;
};

class Date {
public:
  Date() : year(0), month(0), day(0) {}
  Date(int year, int month, int day) : year(year), month(month), day(day) {}
  Date(string str) {
    // cout << "[" << str << "]" << endl;
    stringstream date_stream(str);

    day = -1998;

    char def1, def2;
    date_stream >> year >> def1 >> month >> def2 >> day;

    if (date_stream.bad() || !date_stream.eof() || (def1 != '-') ||
        (def2 != '-') || (day == -1998)) {
      stringstream msg_stream;
      msg_stream << "Wrong date format: " << str;
      throw date_format_exception(msg_stream.str());
    }

    if (month < 1 || month > 12) {
      stringstream msg_stream;
      msg_stream << "Month value is invalid: " << month;
      throw date_format_exception(msg_stream.str());
    }

    if (day < 1 || day > 31) {
      stringstream msg_stream;
      msg_stream << "Day value is invalid: " << day;
      throw date_format_exception(msg_stream.str());
    }
  }
  int GetYear() const { return year; }
  int GetMonth() const { return month; }
  int GetDay() const { return day; }

private:
  int year, month, day;
};

bool operator<(const Date &lhs, const Date &rhs) {
  if (lhs.GetYear() == rhs.GetYear()) {
    if (lhs.GetMonth() == rhs.GetMonth()) {
      return lhs.GetDay() < rhs.GetDay();
    } else {
      return lhs.GetMonth() < rhs.GetMonth();
    }
  } else {
    return lhs.GetYear() < rhs.GetYear();
  }
}

ostream &operator<<(ostream &stream, const Date &date) {
  stream << setw(4) << setfill('0') << date.GetYear();
  stream << "-";
  stream << setw(2) << setfill('0') << date.GetMonth();
  stream << "-";
  stream << setw(2) << setfill('0') << date.GetDay();
  return stream;
}

class Database {
public:
  void AddEvent(const Date &date, const string &event) {
    data[date].insert(event);
  }

  bool DeleteEvent(const Date &date, const string &event) {
    if (data.count(date)) {
      if (data[date].count(event)) {
        ECHO("Deleted successfully");
        data[date].erase(event);
        if (data[date].size() == 0) {
          data.erase(date);
        }
        return true;
      } else {
        ECHO("Event not found");
        return false;
      }
    } else {
      ECHO("Event not found");
      return false;
    }
  }

  int DeleteDate(const Date &date) {
    int count = 0;
    if (data.count(date)) {
      count = data[date].size();
      data.erase(date);
    }
    stringstream msg;
    msg << "Deleted " << count << " events";
    ECHO(msg.str());
    return count;
  }

  void Find(const Date &date) {
    if (data.count(date)) {
      for (const auto &item : data[date]) {
        ECHO(item);
      }
    }
  }

  void Print() const {
    for (const auto &[date, items] : data) {
      for (const auto &item : items) {
        stringstream msg;
        msg << date << " " << item;
        ECHO(msg.str());
      }
    }
  }

private:
  map<Date, set<string>> data;
};

void database(const vector<string> &lines) {
  Database db;

  for (const auto &line : lines) {
    stringstream command_stream(line);
    string command;
    command_stream >> command;
    if (command == "Add") {
      string event;
      string date;

      // reading event and date as plain strings
      command_stream >> date >> event;

      try {
        // converting string to date
        Date the_date(date);

        db.AddEvent(date, event);
      } catch (date_format_exception &e) {
        // in case of error, show message
        stringstream response;
        response << e.getMessage();
        ECHO(response.str());
      }

    } else if (command == "Del") {
      string date;
      string event;

      // reading event and date as plain strings
      command_stream >> date;
      try {
        // converting string to date
        Date the_date(date);

        if (command_stream.eof()) {
          db.DeleteDate(date);
        } else {
          command_stream >> event;
          db.DeleteEvent(date, event);
        }
      } catch (date_format_exception &e) {
        // in case of error, show message
        stringstream response;
        response << e.getMessage();
        ECHO(response.str());
      }
    } else if (command == "Find") {
      string date;
      string event;

      // reading event and date as plain strings
      command_stream >> date;
      try {
        // converting string to date
        Date the_date(date);

        db.Find(date);
      } catch (date_format_exception &e) {
        // in case of error, show message
        stringstream response;
        response << e.getMessage();
        ECHO(response.str());
      }
    } else if (command == "Print") {
      db.Print();
    } else if (command == "") {
    } else {
      stringstream response;
      response << "Unknown command: " << command << endl;
      ECHO(response.str());
    }
  }
}

#ifdef TEST

bool compare(vector<string> output) {
  for (const auto &item : output) {
    string str;
    if (ss.eof()) {
      cout << "ss ended";
      return false;
    }
    getline(ss, str);
    if (str != item) {
      cout << str << " != " << item << endl;
      return false;
    } else {
      cout << "[" << str << "] == [" << item << "]" << endl;
    }
  }
  return true;
}

bool test1() {
  database({
      "Add 0-1-2 event1",
      "Add 1-2-3 event2",
      "Find 0-1-2",
      "",
      "Del 0-1-2",
      "Print",
      "Del 1-2-3 event2",
      "Del 1-2-3 event2",
  });

  return compare({
      "event1",
      "Deleted 1 events",
      "0001-02-03 event2",
      "Deleted successfully",
      "Event not found",
  });
}

bool test2() {
  database({
      "Add 0-13-32 event1",
  });

  return compare({
      "Month value is invalid: 13",
  });

  // return vectors_equal(res, output);
}

bool test3() {
  database({
      "Add 1---1-1 event1",
  });

  return compare({
      "Wrong date format: 1---1-1",
  });
}

bool test4() {
  database({
      "Add 0-11-32 event1",
  });

  return compare({
      "Day value is invalid: 32",
  });
}

bool test5() {
  database({
      "Add 1*1*1 t",
      "Print",
  });

  return compare({
      "Wrong date format: 1*1*1",
  });
}

bool test6() {
  Date d1(102, 1, 12);
  Date d2(1002, 1, 1);

  return d1 < d2;
}

bool test7() {
  database({
      "Add 102-1-12 dd",
      "Add 1002-1-1 dddd",
      "Add 102-1-12 vvv",
      "Add 103-2-1 wwwwwww",
      "Add 103-2-1 rrrr333",
      "Add 103-2-1 aaa223",
      "Print",
  });

  return compare({
      "0102-01-12 dd",
      "0102-01-12 vvv",
      "0103-02-01 aaa223",
      "0103-02-01 rrrr333",
      "0103-02-01 wwwwwww",
      "1002-01-01 dddd",
  });
}

bool test8() {
  database({
      "Add 1-1---1 event1",
  });

  return compare({
      "Wrong date format: 1-1---1",
  });
}

bool test9() {
  database({"Add 1-1- event1", "Add 1-12-31 event1"});

  return compare({
      "Wrong date format: 1-1-",
  });
}

bool test10() {
  database({
      "Print",
  });

  return compare({
      "",
  });
}

bool test11() {
  database({
      "Add 1-1-1 a",
      "Find 1-1-2 b",
  });

  // TODO not sure this test is copletely correct. Should it be no output at
  // all?
  return compare({
      "",
  });
}

bool test12() {
  database({
      "Add 1-1-1 C",
      "Add 1-1-1 A",
      "Add 1-1-1 B",
      "Add 1-2-1 task2",
      "Add 1-1-2 task3",
      "Add 2-1-1 task1",
      "Print",
      "Find 1-1-1",
  });

  return compare({
      "0001-01-01 A",
      "0001-01-01 B",
      "0001-01-01 C",
      "0001-01-02 task3",
      "0001-02-01 task2",
      "0002-01-01 task1",
      "A",
      "B",
      "C",
  });
}

bool test13() {
  database({"Add 1-1-1 a", "Del 1-1-1 a1", "Print"});

  return compare({
      "Event not found",
      "0001-01-01 a",
  });
}

bool test14() {
  database({"Add f8-1-1 task",   "Add 9f-1-1 task",
            "Add 1-11f-1 task",  "Add 1-f12-1 task",
            "Add 1-1-f13 task!", "Add 1-1-14f task",
            "Add --15-1-1 task", "Add 1---2-1 task",
            "Add 1-1---17 task", "Add 1-1- task",
            "Add 1--1 task",     "Add --111 task",
            "Add 1---+++1 task", "Add --++1 task",
            "Add 1-1-f task",    "Add -1 -1 -1 t",
            "Add 1-0- t",        "Add 1-1-1-1 t",
            "Del foo",           "Print"});

  return compare({"Wrong date format: f8-1-1", "Wrong date format: 9f-1-1",
                  "Wrong date format: 1-11f-1", "Wrong date format: 1-f12-1",
                  "Wrong date format: 1-1-f13", "Wrong date format: 1-1-14f",
                  "Wrong date format: --15-1-1", "Wrong date format: 1---2-1",
                  "Wrong date format: 1-1---17", "Wrong date format: 1-1-",
                  "Wrong date format: 1--1", "Wrong date format: --111",
                  "Wrong date format: 1---+++1", "Wrong date format: --++1",
                  "Wrong date format: 1-1-f", "Wrong date format: -1",
                  "Wrong date format: 1-0-", "Wrong date format: 1-1-1-1",
                  "Wrong date format: foo"});
}
#else

#endif

int main() {
#ifdef TEST
  auto tests = {test1, test2, test3,  test4,  test5,  test6,  test7,
                test8, test9, test10, test11, test12, test13, test14};
  auto i = 0;
  bool failed = false;
  for (auto test : tests) {
    i++;
    if (!test()) {
      cout << "TEST " << i << " FAILED" << endl;
      failed = true;
    } else {
      cout << "TEST " << i << " OK" << endl;
    }
    FLUSH();
  }

  if (failed) {
    cout << "SOME TESTS FAILED" << endl;
  } else {
    cout << "ALL TESTS PASSED" << endl;
  }

  return 0;

#else
  vector<string> commands;
  string command;
  while (getline(cin, command)) {
    commands.push_back(command);
  }

  database(commands);

  return 0;
#endif
}