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
        // if (schedule->satellites.at(satellite).type == SatelliteType::KINO && (std::find(possible_actions->shooting.begin(), possible_actions->shooting.end(), satellite) == possible_actions->shooting.end()))
        double filled = schedule->int_to_satellites.at(satellite).getFilledSpace();
        if (filled > most_filled) {
            most_filled = filled;
            station->chosen_satellite = satellite;
        }
    }
    if (station->chosen_satellite != -1) {
        schedule->all_received_data += schedule->int_to_satellites.at(station->chosen_satellite).transferData(interval.second - interval.first);
    }
    auto index = std::find(possible_actions->shooting.begin(), possible_actions->shooting.end(), station->chosen_satellite);
    if (index != possible_actions->shooting.end()) {
        not_selected_shootings.push_back(int(std::distance(possible_actions->shooting.begin(), index)));
    }
}

void Slot::choose_satellite(Station* station) {
    for (auto& satellite : station->visible_satellites) {
        auto transferring_index = std::find(transferring_satellites.begin(), transferring_satellites.end(), satellite);
        if (transferring_index == transferring_satellites.end()) {
            auto satellite_index = std::find(possible_actions->shooting.begin(), possible_actions->shooting.end(), satellite);
            if (schedule->int_to_satellites.at(satellite).getTransferSpeed() == KINO_TRANSFER_SPEED) {
                if (satellite_index == possible_actions->shooting.end() && schedule->int_to_satellites.at(satellite).getFilledSpace() >= OCCUPANCY_FOR_TRANSFER) {
                    if (station->chosen_satellite == -1) {
                        station->chosen_satellite = satellite;
                    }
                    else {
                        if (schedule->int_to_satellites.at(satellite).getFilledSpace() > schedule->int_to_satellites.at(station->chosen_satellite).getFilledSpace()) {
                            station->chosen_satellite = satellite;
                        }
                    }
                }
            }
            else {
                station->possible_satellites.push_back(satellite);
            }
        }
    }
    if (station->chosen_satellite == -1) {
        double most_filled = 0;
        for (auto sat : station->possible_satellites) {
            double filled = schedule->int_to_satellites.at(sat).getFilledSpace();
            if (filled > most_filled) {
                most_filled = filled;
                station->chosen_satellite = sat;
            }
        }
        station->possible_satellites.clear();
        auto index = std::find(possible_actions->shooting.begin(), possible_actions->shooting.end(), station->chosen_satellite);
        if (index != possible_actions->shooting.end()) {
            not_selected_shootings.push_back(int(std::distance(possible_actions->shooting.begin(), index)));
        }
    }
    if (station->chosen_satellite != -1) {
        schedule->all_received_data += schedule->int_to_satellites.at(station->chosen_satellite).transferData(interval.second - interval.first);
        transferring_satellites.push_back(station->chosen_satellite);
    }
    //station->chosen_satellite = -1;
}

void Slot::makeOptimalChoice() {
    for (auto& transferring_action : possible_actions->transferring) {
        choose_most_filled(&(schedule->int_to_stations.at(transferring_action)));
    }
    for (int i = 0; i < possible_actions->shooting.size(); ++i) {
        if (std::find(not_selected_shootings.begin(), not_selected_shootings.end(), i) == not_selected_shootings.end()) {
            schedule->int_to_satellites.at(possible_actions->shooting[i]).writeData(interval.second - interval.first);
        }
    }
}

void Slot::makeAnotherOptimalChoice() {
    for (auto& transferring_action : possible_actions->transferring) {
        schedule->int_to_stations.at(transferring_action).chosen_satellite = -1;
        choose_satellite(&(schedule->int_to_stations.at(transferring_action)));
    }
    for (int i = 0; i < possible_actions->shooting.size(); ++i) {
        if (std::find(not_selected_shootings.begin(), not_selected_shootings.end(), i) == not_selected_shootings.end()) {
            schedule->int_to_satellites.at(possible_actions->shooting[i]).writeData(interval.second - interval.first);
        }
    }
}

std::string Slot::toString() {
    std::ostringstream oss;
    oss << "[" << interval.first << ", " << interval.second << "]\nShooting:\n";
    for (int i = 0; i < possible_actions->shooting.size(); ++i) {
        if (std::find(not_selected_shootings.begin(), not_selected_shootings.end(), i) == not_selected_shootings.end()) {
            oss << "Satellite-KinoSat_" << schedule->int_to_str_satellites.at(possible_actions->shooting[i]) << "\n";
        }
    }
    oss << "\nTransferring:\n";
    for (auto& transferring_action : possible_actions->transferring) {
        if (schedule->int_to_stations.at(transferring_action).chosen_satellite != -1) {
            oss << schedule->int_to_str_stations.at(transferring_action) << ":Satellite-KinoSat_" << schedule->int_to_str_satellites.at(schedule->int_to_stations.at(transferring_action).chosen_satellite) << "\n";
        }
    }
    return oss.str();
}