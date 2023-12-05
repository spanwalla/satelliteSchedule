//
// Created by wwwod on 30.11.2023.
//

#include "Event.h"

Event::Event(EventType type, std::chrono::time_point<std::chrono::system_clock> timestamp, const std::string& satellite,
    const std::string& station) : type(type), timestamp(timestamp), action(std::make_pair(satellite, station)) {

}

bool Event::operator< (const Event& other) const {
    return timestamp < other.timestamp;
}

bool Event::operator != (const Event& other) const {
    return timestamp != other.timestamp;
}

/* bool operator==(const Event& first, const Event& second) {
    return first.timestamp == second.timestamp;
}

bool operator!=(const Event& first, const Event& second) {
    return first.timestamp != second.timestamp;
} */