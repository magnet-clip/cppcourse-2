#include "bus_manager.h"

void BusManager::AddBus(const string &bus, const vector<string> &stops) {
  for (auto stop : stops) {
    stops_for_bus[bus].push_back(stop);
    buses_for_stop[stop].push_back(bus);
  }
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const {
  if (!buses_for_stop.count(stop)) {
    return {};
  } else {
    return buses_for_stop.at(stop);
  }
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const { return {stops_for_bus}; }