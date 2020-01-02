#include "bus_manager.h"
#include "query.h"
#include "responses.h"
#include "test_runner.h"

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
  // TestAll();

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