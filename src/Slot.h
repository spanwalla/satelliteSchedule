//
// Created by wwwod on 01.12.2023.
//

#ifndef SATELLITESCHEDULE_SLOT_H
#define SATELLITESCHEDULE_SLOT_H

#include <chrono>
#include <stdexcept>
#include <iostream>
#include <random>
#include <sstream>
#include "Event.h"

class Schedule;

class Slot {
public:
    Slot(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end, std::vector<std::pair<std::string, std::string>>* actions);
    void makeNotOptimalChoose(Schedule& schedule);
    std::string toString();
    friend std::ostream& operator<<(std::ostream& os, Slot& object);
private:
    std::vector<std::pair<std::string, std::string>>* possible_actions;
    std::pair<std::chrono::time_point<std::chrono::system_clock>, std::chrono::time_point<std::chrono::system_clock>> interval;
    std::vector<int> selected_actions;
};


#endif //SATELLITESCHEDULE_SLOT_H