#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "responses.h"

class BusManager {
private:
  map<string, vector<string>> stops_for_bus;
  map<string, vector<string>> buses_for_stop;

public:
  void AddBus(const string &bus, const vector<string> &stops);

  BusesForStopResponse GetBusesForStop(const string &stop) const;

  StopsForBusResponse GetStopsForBus(const string &bus) const;

  AllBusesResponse GetAllBuses() const;
};