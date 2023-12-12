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
    Event(EventType type, std::chrono::time_point<std::chrono::system_clock> timestamp, int satellite, int station = -1);
    bool operator< (const Event& other) const;
    bool operator != (const Event& other) const;
    // friend bool operator== (const Event& first, const Event& second);
    // friend bool operator!= (const Event& first, const Event& second);

    EventType type;
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    std::pair<int, int> action;
};

#endif //SATELLITESCHEDULE_EVENT_H
