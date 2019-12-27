
#include "responses.h"

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