//
// Created by wwwod on 01.12.2023.
//

#include "Slot.h"
#include "Schedule.h"

Slot::Slot(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end, Actions* actions, Schedule* schedule) 
    : interval(std::make_pair(start, end)), possible_actions(actions), schedule(schedule) {
    if (interval.first >= interval.second)
        throw std::invalid_argument("End of slot is earlier than start.");
}

/*void Slot::makeNotOptimalChoose(Schedule& schedule) {
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
}*/

void Slot::choose_most_filled(Station* station) {
    double most_filled = 0;
    for (auto& satellite : station->visible_satellites) {
        //if (schedule->satellites.at(satellite).type == SatelliteType::KINO && (std::find(possible_actions->shooting.begin(), possible_actions->shooting.end(), satellite) == possible_actions->shooting.end()))
        double filled = schedule->satellites.at(satellite).getFilledSpace();
        if (filled > most_filled) {
            most_filled = filled;
            station->chosen_satellite = satellite;
        }
    }
    if (!station->chosen_satellite.empty()) {
        schedule->all_received_data += schedule->satellites.at(station->chosen_satellite).transferData(interval.second - interval.first);
    }
    std::vector<std::string>::const_iterator ind = std::find(possible_actions->shooting.begin(), possible_actions->shooting.end(), station->chosen_satellite);
    if (ind != possible_actions->shooting.end()) {
        not_selected_shootings.push_back(ind - possible_actions->shooting.begin());
    }
}

void Slot::makeOptimalChoice() {
    for (auto& transfering_action : (*possible_actions).transfering) {
        choose_most_filled(&(schedule->stations.at(transfering_action)));
    }
    for (int i = 0; i < possible_actions->shooting.size(); ++i) {
        if (std::find(not_selected_shootings.begin(), not_selected_shootings.end(), i) == not_selected_shootings.end()) {
            schedule->satellites.at(possible_actions->shooting[i]).writeData(interval.second - interval.first);
        }
    }
}

std::ostream& operator<<(std::ostream& os, Slot& object) {
    return os << object.toString();
}

std::string Slot::toString() {
    std::ostringstream oss;
    oss << "[" << interval.first << ", " << interval.second << "] Action: ";
    for (int i = 0; i < possible_actions->shooting.size(); ++i) {
        if (std::find(not_selected_shootings.begin(), not_selected_shootings.end(), i) == not_selected_shootings.end()) {
            oss << "Satellite-KinoSat_" << possible_actions->shooting[i] << " shooting";
        }
    }
    oss << "\n";
    for (auto& transfering_action : (*possible_actions).transfering) {
        if (!schedule->stations.at(transfering_action).chosen_satellite.empty()) {
            oss << transfering_action << " get info from: " << schedule->stations.at(transfering_action).chosen_satellite;
        }
    }
    return oss.str();
}