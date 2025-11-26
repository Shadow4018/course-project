#include "Flight.h"
#include <string>
#include <sstream>

/// CONSTRUCTORS && DESTRUCTOR ///
Flight::Flight()
    : raceNo(0),
    route(make_pair("none", "none")),
    stops({ "none" }),
    departureTime("00:00"),
    flightTime(0),
    availableSeats(0) {
}

Flight::Flight(const int& _raceNo, const pair<string, string>& _route, 
    const list<string>& _stops, const string& _departureTime, 
    const int& _flightTime, const int& _availableSeats) : raceNo(_raceNo),
    route(_route), stops(_stops), departureTime(_departureTime), 
    flightTime(_flightTime), availableSeats(_availableSeats) {
}

Flight::Flight(const Flight& other)
    : raceNo(other.raceNo),
    route(other.route),
    stops(other.stops),
    departureTime(other.departureTime),
    flightTime(other.flightTime),
    availableSeats(other.availableSeats) {
}

Flight::Flight(Flight&& other) noexcept
    : raceNo(move(other.raceNo)),
    route(move(other.route)),
    stops(move(other.stops)),
    departureTime(move(other.departureTime)),
    flightTime(move(other.flightTime)),
    availableSeats(move(other.availableSeats)) {
}

Flight::~Flight() = default;

/// GETTERS && SETTERS ///
int Flight::getRaceNo() const { return raceNo; }
const pair<string, string>& Flight::getRoute() const { return route; }
const list<string>& Flight::getStops() const { return stops; }
const string& Flight::getDepartureTime() const { return departureTime; }
int Flight::getFlightTime() const { return flightTime; }
int Flight::getAvailableSeats() const { return availableSeats; }

/// SETTERS ///
void Flight::setNo(int newNo) { raceNo = newNo; }
void Flight::setRoute(pair<string, string> newRoute) { route = newRoute; }
void Flight::setStops(list<string> newStops) { stops = newStops; }
void Flight::setDepartureTime(string newDepartureTime) { departureTime = newDepartureTime; }
void Flight::setFlightTime(int newFlightTime) { flightTime = newFlightTime; }
void Flight::setAvailableSeats(int newAvailableSeats) { availableSeats = newAvailableSeats; }

/// MAIN METHODS ///
bool Flight::hasStop(const string& stopName) const {
    for (const auto& stop : stops) {
        if (stop == stopName) return true;
    }
    return false;
}

string Flight::getRouteString() const {
    return route.first + " - " + route.second;
}

int Flight::getTotalStops() const {
    if (stops.size() == 1 && stops.front() == "none") return 0;
    return static_cast<int>(stops.size());
}

bool Flight::isFull() const {
    return availableSeats <= 0;
}

string Flight::toCSV() const {
    stringstream ss;
    ss << raceNo << ","
        << route.first << "-" << route.second << ",";

    bool first = true;
    for (const auto& stop : stops) {
        if (!first) ss << ";";
        ss << stop;
        first = false;
    }

    ss << "," << departureTime
        << "," << flightTime
        << "," << availableSeats;
    return ss.str();
}