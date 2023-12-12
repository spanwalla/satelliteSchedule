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
    auto ind = std::find(possible_actions->shooting.begin(), possible_actions->shooting.end(), station->chosen_satellite);
    if (ind != possible_actions->shooting.end()) {
        not_selected_shootings.push_back(int(std::distance(possible_actions->shooting.begin(), ind)));
    }
}

void Slot::makeOptimalChoice() {
    for (auto& transferring_action : possible_actions->transferring) {
        choose_most_filled(&(schedule->stations.at(transferring_action)));
    }
    for (int i = 0; i < possible_actions->shooting.size(); ++i) {
        if (std::find(not_selected_shootings.begin(), not_selected_shootings.end(), i) == not_selected_shootings.end()) {
            schedule->satellites.at(possible_actions->shooting[i]).writeData(interval.second - interval.first);
        }
    }
}

std::string Slot::toString() {
    std::ostringstream oss;
    oss << "[" << interval.first << ", " << interval.second << "]\nShooting:\n";
    for (int i = 0; i < possible_actions->shooting.size(); ++i) {
        if (std::find(not_selected_shootings.begin(), not_selected_shootings.end(), i) == not_selected_shootings.end()) {
            oss << "Satellite-KinoSat_" << possible_actions->shooting[i] << "\n";
        }
    }
    oss << "\nTransferring:\n";
    for (auto& transferring_action : possible_actions->transferring) {
        if (!schedule->stations.at(transferring_action).chosen_satellite.empty()) {
            oss << transferring_action << ":Satellite-KinoSat_" << schedule->stations.at(transferring_action).chosen_satellite << "\n";
        }
    }
    return oss.str();
}