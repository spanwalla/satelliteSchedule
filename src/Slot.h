//
// Created by wwwod on 01.12.2023.
//

#ifndef SATELLITESCHEDULE_SLOT_H
#define SATELLITESCHEDULE_SLOT_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <stdexcept>
#include <iostream>
#include <random>
#include <sstream>
#include "Event.h"
#include "Actions.h"

class Schedule;

class Slot {
public:
    Slot(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end, Actions* actions, Schedule* schedule);
    void makeOptimalChoice();
    void makeAnotherOptimalChoice();
    std::string toString();

private:
    Actions* possible_actions;
    Schedule* schedule;
    std::pair<std::chrono::time_point<std::chrono::system_clock>, std::chrono::time_point<std::chrono::system_clock>> interval;
    std::vector<int> not_selected_shootings;
    std::vector<int> transmitting_satellites;
    void chooseMostFilled(Station* station);
    void chooseSatellite(Station* station, int station_ind);
    bool visibleByOther(int start, int satellite);
};

#ifndef _WIN32
template <typename Clock, typename Duration>
std::ostream& operator<<(std::ostream& os, const std::chrono::time_point<Clock, Duration>& time_point) {
    std::time_t t = Clock::to_time_t(time_point);
    std::tm tm = *std::localtime(&t);
    os << std::put_time(&tm, "%F %T") << '.' << std::setfill('0') << std::setw(3)
       << std::chrono::duration_cast<std::chrono::milliseconds>(time_point.time_since_epoch()).count() % 1000;
    return os;
}
#endif //_WIN32
#endif //SATELLITESCHEDULE_SLOT_H