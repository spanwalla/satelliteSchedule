//
// Created by wwwod on 30.11.2023.
//

#ifndef SATELLITESCHEDULE_EVENT_H
#define SATELLITESCHEDULE_EVENT_H

#include <chrono>
#include <stdexcept>
#include "EventType.h"
#include "Satellite.h"
#include "Station.h"

class Event {
public:
    Event(EventType type, std::chrono::time_point<std::chrono::system_clock> timestamp, const std::string& satellite, const std::string& station = "");
    bool operator< (const Event& other) const;
    // friend bool operator== (const Event& first, const Event& second);
    // friend bool operator!= (const Event& first, const Event& second);

    EventType type;
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    std::pair<std::string, std::string> action;
};

#endif //SATELLITESCHEDULE_EVENT_H
