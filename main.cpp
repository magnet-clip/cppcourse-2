#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class QueryType { NewBus, BusesForStop, StopsForBus, AllBuses };

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream &operator>>(istream &is, Query &q) {
  string operation_code;
  is >> operation_code;

  if (operation_code == "NEW_BUS") {
    string bus;
    is >> bus;

    int stop_count;
    is >> stop_count;

    vector<string> stops;
    stops.resize(stop_count);
    for (string &stop : stops) {
      is >> stop;
    }

    q.type = QueryType::NewBus;
    q.bus = bus;
    q.stops = stops;
  } else if (operation_code == "BUSES_FOR_STOP") {
    string stop;
    cin >> stop;

    q.type = QueryType::BusesForStop;
    q.stop = stop;
  } else if (operation_code == "STOPS_FOR_BUS") {
    string bus;
    cin >> bus;

    q.type = QueryType::StopsForBus;
    q.bus = bus;
  } else if (operation_code == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }
  return is;
}

using BusesForStopResponse = vector<string>;

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
  if (r.size() > 0) {
    for (const auto &item : r) {
      os << item << " ";
    }
  } else {
    os << "No stop";
  }
  return os;
}

using StopsForBusResponse = map<string, vector<string>>;

ostream &operator<<(ostream &os, const StopsForBusResponse &r) {
  if (!r.size()) {
    os << "No bus";
  } else {
    auto i = 0;
    for (const auto &[stop, buses] : r) {
      os << "Stop " << stop << ": ";
      if (!buses.size()) {
        os << "no interchange";
      } else {
        for (const string &bus : buses) {
          os << bus << " ";
        }
      }
      if (++i < r.size()) {
        os << endl;
      }
    }
  }
  return os;
}

struct AllBusesResponse {
   map<string, vector<string>> buses;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r) {
  const auto &buses_to_stops = r.buses;

  if (buses_to_stops.empty()) {
    os << "No buses";
  } else {
    auto i = 0;
    for (const auto &[bus, stops] : buses_to_stops) {
      os << "Bus " << bus << ": ";
      for (const string &stop : stops) {
        os << stop << " ";
      }
      if (++i < stops.size()) {
        os << endl;
      }
    }
  }

  return os;
}

class BusManager {
private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;

public:
  void AddBus(const string &bus, const vector<string> &stops) {
    for (const auto &stop : stops) {
      buses_to_stops[bus].push_back(stop);
      stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string &stop) const {
    if (stops_to_buses.count(stop) == 0) {
      return {};
    } else {
      return {stops_to_buses.at(stop)};
    }
  }

  StopsForBusResponse GetStopsForBus(const string &bus) const {
    if (buses_to_stops.count(bus) == 0) {
      return {};
    } else {
      map<string, vector<string>> response;
      for (const string &stop : buses_to_stops.at(bus)) {
        if (stops_to_buses.at(stop).size() == 1) {
          response[stop] = {};
        } else {
          for (const string &other_bus : stops_to_buses.at(stop)) {
            if (bus != other_bus) {
              response[stop].push_back(other_bus);
            }
          }
        }
      }
      return {response};
    }
  }

  AllBusesResponse GetAllBuses() const { return {buses_to_stops}; }
};

template <class T> ostream &operator<<(ostream &os, const set<T> &s) {
  os << "{";
  bool first = true;
  for (const auto &x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
  bool first = true;
  os << "[";
  for (const auto &item : v) {
    if (!first) {
      os << ", ";
    }
    os << item;

    first = false;
  }
  return os << "]";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
  os << "{";
  bool first = true;
  for (const auto &kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u << " hint: " << hint;
    throw runtime_error(os.str());
  }
}

inline void Assert(bool b, const string &hint) { AssertEqual(b, true, hint); }

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string &test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (runtime_error &e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

void TestExact() {
  BusManager bm;
  bm.AddBus("32", {"Tolstopaltsevo", "Marushkino", "Vnukovo"});
  bm.AddBus("32K", {"Tolstopaltsevo", "Marushkino", "Vnukovo", "Peredelkino",
                    "Solntsevo", "Skolkovo"});

  vector<string> x = {"32", "32K"};
  AssertEqual(bm.GetBusesForStop("Vnukovo"), x, "Order");

  bm.AddBus("950", {"Kokoshkino", "Marushkino", "Vnukovo", "Peredelkino",
                    "Solntsevo", "Troparyovo"});
  bm.AddBus("272", {"Vnukovo", "Moskovsky", "Rumyantsevo", "Troparyovo"});

  map<string, vector<string>> y = {{"Vnukovo", {"32", "32K", "950"}},
                                   {"Moskovsky", {}},
                                   {"Rumyantsevo", {}},
                                   {"Troparyovo", {"950"}}};
  AssertEqual(bm.GetStopsForBus("272"), y, "Order 1");

  map<string, vector<string>> z = {
      {"Rumyantsevo", {}},
      {"Troparyovo", {"950"}},
      {"Vnukovo", {"32", "32K", "950"}},
      {"Moskovsky", {}},
  };
  AssertEqual(bm.GetStopsForBus("272"), z, "Order 2");

  cout << bm.GetStopsForBus("272") << endl;
}

void TestStopsExist() {
  BusManager bm;
  bm.AddBus("AAA", {"A1", "A2", "A3"});

  vector<string> x = {"AAA"};
  AssertEqual(bm.GetBusesForStop("A1"), x, "Order");
  AssertEqual(bm.GetBusesForStop("A2"), x, "Order");
  AssertEqual(bm.GetBusesForStop("A3"), x, "Order");
}

void TestStopsExist2() {
  BusManager bm;
  bm.AddBus("AAA", {"A1", "A2", "A3"});
  bm.AddBus("BBB", {"A1", "B1", "B2"});

  vector<string> y = {"AAA", "BBB"};
  AssertEqual(bm.GetBusesForStop("A1"), y, "Order 1");
  vector<string> x = {"AAA"};
  AssertEqual(bm.GetBusesForStop("A2"), x, "Order 2");
  AssertEqual(bm.GetBusesForStop("A3"), x, "Order 3");
  vector<string> z = {"BBB"};
  AssertEqual(bm.GetBusesForStop("B1"), z, "Order 4");
  AssertEqual(bm.GetBusesForStop("B2"), z, "Order 5");
}

void TestStopsForBus() {
  BusManager bm;
  bm.AddBus("AAA", {"A1", "A2", "A3"});
  bm.AddBus("BBB", {"A1", "B1", "B2"});

  map<string, vector<string>> y = {{"A1", {"BBB"}}, {"A2", {}}, {"A3", {}}};
  AssertEqual(bm.GetStopsForBus("AAA"), y, "Order");
  // AssertEqual(bm.GetStopsForBus("BBB"), x, "Order");
}

void TestAll() {
  TestRunner tr;

  tr.RunTest(TestExact, "Exact");
  tr.RunTest(TestStopsExist, "Stops should exist");
  tr.RunTest(TestStopsExist2, "Stops should exist 2");
  tr.RunTest(TestStopsForBus, "Stops should exist");
}

int main() {
  TestAll();

  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}