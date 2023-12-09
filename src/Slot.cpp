//
// Created by wwwod on 01.12.2023.
//

#include "Slot.h"
#include "Schedule.h"

Slot::Slot(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end, std::vector<std::pair<std::string, std::string>>* actions) : interval(std::make_pair(start, end)), possible_actions(actions) {
    if (interval.first >= interval.second)
        throw std::invalid_argument("End of slot is earlier than start.");
}

void Slot::makeNotOptimalChoose(Schedule& schedule) {
    if (!possible_actions->empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, int((*possible_actions).size()) - 1);
        selected_action = dist(gen);
        chosen_actions.push_back((*possible_actions)[selected_action]);
        if (chosen_actions[0].second.empty()) {
            schedule.satellites.at(chosen_actions[0].first).writeData(interval.second - interval.first);
        }
        else {
            schedule.all_received_data += schedule.stations.at(chosen_actions[0].second).receiveData(schedule.satellites.at(chosen_actions[0].first), interval.second - interval.first);
        }
    }
}

void Slot::chooseFirstPossibleAction(Schedule& schedule) {
    if (!possible_actions->empty()) {
        chosen_actions.push_back((*possible_actions)[0]);
        if ((*possible_actions)[0].second.empty()) {
            schedule.satellites.at((*possible_actions)[0].first).writeData(interval.second - interval.first);
        }
        else {
            schedule.all_received_data += schedule.stations.at((*possible_actions)[0].second).receiveData(schedule.satellites.at((*possible_actions)[0].first), interval.second - interval.first);
        }
    }
}

std::string Slot::toString() {
    std::ostringstream oss;
    oss << "[" << interval.first << ", " << interval.second << "] Action: ";
    for (auto & chosen_action : chosen_actions) {
        oss << "Satellite-KinoSat_" << chosen_action.first;
        if (chosen_action.second.empty())
            oss << " shooting.";
        else
            oss << " transfers to " << chosen_action.second << ".";
    }
    return oss.str();
}