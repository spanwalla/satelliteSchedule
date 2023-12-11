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
#include "Actions.h"

class Schedule;

class Slot {
public:
    Slot(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end, Actions* actions, Schedule* schedule);
    void makeOptimalChoice();
    std::string toString();
    friend std::ostream& operator <<(std::ostream& os, Slot& object);

private:
    Actions* possible_actions;
    Schedule* schedule;
    std::pair<std::chrono::time_point<std::chrono::system_clock>, std::chrono::time_point<std::chrono::system_clock>> interval;
    std::vector<int> not_selected_shootings;
    void choose_most_filled(Station* station);
};


#endif //SATELLITESCHEDULE_SLOT_H