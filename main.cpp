#include "test_runner.h"
#include <algorithm>
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

using StopsForBusResponse = vector<pair<string, vector<string>>>;

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
  map<string, vector<string>> stops_for_bus;
  map<string, vector<string>> buses_for_stop;

public:
  void AddBus(const string &bus, const vector<string> &stops) {
    for (auto stop : stops) {
      stops_for_bus[bus].push_back(stop);
      buses_for_stop[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string &stop) const {
    if (!buses_for_stop.count(stop)) {
      return {};
    } else {
      return buses_for_stop.at(stop);
    }
  }

  StopsForBusResponse GetStopsForBus(const string &bus) const {
    if (!stops_for_bus.count(bus)) {
      return {};
    } else {
      vector<pair<string, vector<string>>> res;
      for (auto stop : stops_for_bus.at(bus)) {
        vector<string> buses_for_this_stop = buses_for_stop.at(stop);
        auto search_iterator =
            find(buses_for_this_stop.begin(), buses_for_this_stop.end(), bus);
        buses_for_this_stop.erase(search_iterator);
        res.push_back(make_pair(stop, buses_for_this_stop));
      }
      return {res};
    }
  }

  AllBusesResponse GetAllBuses() const { return {stops_for_bus}; }
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

  vector<pair<string, vector<string>>> y = {{"Vnukovo", {"32", "32K", "950"}},
                                            {"Moskovsky", {}},
                                            {"Rumyantsevo", {}},
                                            {"Troparyovo", {"950"}}};
  AssertEqual(bm.GetStopsForBus("272"), y, "Order 1");
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

  vector<pair<string, vector<string>>> y = {
      {"A1", {"BBB"}}, {"A2", {}}, {"A3", {}}};
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