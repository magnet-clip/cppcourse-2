#pragma once

#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

using BusesForStopResponse = vector<string>;

using StopsForBusResponse = vector<pair<string, vector<string>>>;

struct AllBusesResponse {
  map<string, vector<string>> buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r);

ostream &operator<<(ostream &os, const StopsForBusResponse &r);

ostream &operator<<(ostream &os, const AllBusesResponse &r);