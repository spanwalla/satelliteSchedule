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

void Slot::chooseMostFilled(Station* station) {
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
        schedule->addData(
                schedule->int_to_satellites.at(station->chosen_satellite).transmitData(interval.second - interval.first));
    }
    auto index = std::find(possible_actions->shooting.begin(), possible_actions->shooting.end(), station->chosen_satellite);
    if (index != possible_actions->shooting.end()) {
        not_selected_shootings.push_back(int(std::distance(possible_actions->shooting.begin(), index)));
    }
}

bool Slot::visibleByOther(int start, int satellite){
    for (int i = start + 1; i < possible_actions->transmitting.size(); ++i) {
        auto index = std::find(schedule->int_to_stations.at(possible_actions->transmitting[i]).visible_satellites.begin(), schedule->int_to_stations.at(possible_actions->transmitting[i]).visible_satellites.end(), satellite);
        if (index != schedule->int_to_stations.at(possible_actions->transmitting[i]).visible_satellites.end()) {
            return true;
        }
    }
    return false;
}

void Slot::chooseSatellite(Station* station, int station_ind) {
    for (auto& satellite : station->visible_satellites) {
        auto transmitting_index = std::find(transmitting_satellites.begin(), transmitting_satellites.end(), satellite);
        if (transmitting_index == transmitting_satellites.end()) {
            auto satellite_index = std::find(possible_actions->shooting.begin(), possible_actions->shooting.end(), satellite);
            if (schedule->int_to_satellites.at(satellite).getTransmitterSpeed() == KINO_TRANSMITTER_SPEED) {
                if (satellite_index == possible_actions->shooting.end() && (schedule->int_to_satellites.at(satellite).getFilledSpace() >= OCCUPANCY_FOR_TRANSMITTING) && !visibleByOther(station_ind, satellite)) {
                    if (station->chosen_satellite == -1) {
                        station->chosen_satellite = satellite;
                    }
                    else {
                        if ((schedule->int_to_satellites.at(satellite).getFilledSpace() > schedule->int_to_satellites.at(station->chosen_satellite).getFilledSpace()) && !visibleByOther(station_ind, satellite)) {
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
            auto transmitter_index = std::find(transmitting_satellites.begin(), transmitting_satellites.end(), sat);
            double filled = schedule->int_to_satellites.at(sat).getFilledSpace();
            if (filled > most_filled && transmitter_index == transmitting_satellites.end()) {
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
        schedule->addData(
                schedule->int_to_satellites.at(station->chosen_satellite).transmitData(interval.second - interval.first));
        transmitting_satellites.push_back(station->chosen_satellite);
    }
    // station->chosen_satellite = -1;
}

void Slot::makeOptimalChoice() {
    for (auto& transmitting_action : possible_actions->transmitting) {
        chooseMostFilled(&(schedule->int_to_stations.at(transmitting_action)));
    }
    for (int i = 0; i < possible_actions->shooting.size(); ++i) {
        if (std::find(not_selected_shootings.begin(), not_selected_shootings.end(), i) == not_selected_shootings.end()) {
            schedule->int_to_satellites.at(possible_actions->shooting[i]).writeData(interval.second - interval.first);
        }
    }
}

void Slot::makeAnotherOptimalChoice() {
    int station_ind = 0;
    for (auto& transmitting_action : possible_actions->transmitting) {
        schedule->int_to_stations.at(transmitting_action).chosen_satellite = -1;
        chooseSatellite(&(schedule->int_to_stations.at(transmitting_action)), station_ind);
        station_ind += 1;
    }
    for (int i = 0; i < possible_actions->shooting.size(); ++i) {
        if (std::find(not_selected_shootings.begin(), not_selected_shootings.end(), i) == not_selected_shootings.end()) {
            if (schedule->int_to_satellites.at(possible_actions->shooting[i]).hasFreeSpace())
                schedule->int_to_satellites.at(possible_actions->shooting[i]).writeData(interval.second - interval.first);
            else
                not_selected_shootings.push_back(i);
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
    oss << "\nTransmitting:\n";
    for (auto& transmitting_action : possible_actions->transmitting) {
        if (schedule->int_to_stations.at(transmitting_action).chosen_satellite != -1) {
            oss << schedule->int_to_str_stations.at(transmitting_action) << ":Satellite-KinoSat_" << schedule->int_to_str_satellites.at(schedule->int_to_stations.at(transmitting_action).chosen_satellite) << "\n";
        }
    }
    return oss.str();
}