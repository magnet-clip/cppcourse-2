#include "condition_parser.h"
#include "database.h"
#include "date.h"
#include "node.h"
#include "test_runner.h"
#include "util.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream &is) {
  string s;
  getline(is, s);
  s.erase(s.begin(),
          find_if(s.begin(), s.end(), [](int ch) { return !isspace(ch); }));
  return s;
}

void TestAll();
/*
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
}*/

int main() {
  TestAll();

  Database db;

  for (string line; getline(cin, line);) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto &entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
        cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument &) {
        cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ",
                "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"},
                "Parse multiple events");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
}