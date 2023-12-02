//
// Created by wwwod on 01.12.2023.
//

#ifndef SATELLITESCHEDULE_SLOT_H
#define SATELLITESCHEDULE_SLOT_H

#include <chrono>
#include <stdexcept>
#include <iostream>
#include <random>
// #include "Schedule.h"
#include "Event.h"

class Schedule;

class Slot {
public:
    Slot(Schedule* schedule, std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end);
    void makeNotOptimalChoose();
    friend std::ostream& operator<<(std::ostream& os, const Slot& object);
private:
    Schedule* schedule;
    std::pair<std::chrono::time_point<std::chrono::system_clock>, std::chrono::time_point<std::chrono::system_clock>> interval;
    std::vector<std::pair<std::string, std::string>> possible_actions;
    int selected_action {-1};
};


#endif //SATELLITESCHEDULE_SLOT_H
