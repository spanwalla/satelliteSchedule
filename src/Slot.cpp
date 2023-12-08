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
        selected_actions.push_back(dist(gen));
        for (auto& selected_action : selected_actions) {
            if ((*possible_actions)[selected_action].second.empty()) {
                schedule.satellites.at((*possible_actions)[selected_action].first).writeData(interval.second - interval.first);
            }
            else {
                schedule.all_received_data += schedule.satellites.at((*possible_actions)[selected_action].first).transferData(interval.second - interval.first);
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, Slot& object) {
    return os << object.toString();
}

std::string Slot::toString() {
    std::ostringstream oss;
    oss << "[" << interval.first << ", " << interval.second << "] Action: ";
    for (auto& selected_action : selected_actions) {
        oss << "Satellite-KinoSat_" << (*possible_actions)[selected_action].first;
        if ((*possible_actions)[selected_action].second.empty())
            oss << " shooting.";
        else
            oss << " transfers to " << (*possible_actions)[selected_action].second << ".";
    }
    return oss.str();
}