#include "query.h"
#include <iostream>

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
