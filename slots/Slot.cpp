//
// Created by wwwod on 01.12.2023.
//

#include "Slot.h"
#include "Schedule.h"

Slot::Slot(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end, std::vector<std::pair<std::string, std::string>>* actions) : interval(std::make_pair(start, end)), possible_actions(actions) {
    if (interval.first >= interval.second)
        throw std::invalid_argument("End of slot is earlier than start.");
    // добавить инициализацию доступных действий
}

void Slot::makeNotOptimalChoose(Schedule& schedule) {
    if (possible_actions->size() != 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, int((*possible_actions).size()) - 1);
        selected_action = dist(gen);
        chosen_actions.push_back((*possible_actions)[selected_action]);
        if (chosen_actions[0].second.empty()) {
            schedule.satellites.at(chosen_actions[0].first).writeData(interval.second - interval.first);
            //std::cout << schedule.satellites.at((*possible_actions)[0].first) << std::endl;
        }
        else {
            schedule.all_received_data += schedule.stations.at(chosen_actions[0].second).receiveData(schedule.satellites.at(chosen_actions[0].first), interval.second - interval.first);
            //std::cout << schedule.satellites.at((*possible_actions)[0].first) << std::endl;
            //std::cout << schedule.stations.at((*possible_actions)[0].second) << std::endl;
        }
    }
}

void Slot::chooseFirstPossibleAction(Schedule& schedule) {
    if (possible_actions->size() != 0) {
        chosen_actions.push_back((*possible_actions)[0]);
        if ((*possible_actions)[0].second.empty()) {
            schedule.satellites.at((*possible_actions)[0].first).writeData(interval.second - interval.first);
            //std::cout << schedule.satellites.at((*possible_actions)[0].first) << std::endl;
        }
        else {
            schedule.all_received_data += schedule.stations.at((*possible_actions)[0].second).receiveData(schedule.satellites.at((*possible_actions)[0].first), interval.second - interval.first);
            //std::cout << schedule.satellites.at((*possible_actions)[0].first) << std::endl;
            //std::cout << schedule.stations.at((*possible_actions)[0].second) << std::endl;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Slot& object) {

    os << "[" << object.interval.first << ", " << object.interval.second << "] Action: ";
    /*if (object.selected_action == -1)
        os << "not chosen.";
    else {
        os << "Satellite-KinoSat_" << object.possible_actions.at(object.selected_action).first;
        if (object.possible_actions.at(object.selected_action).second.empty())
            os << " shooting.";
        else
            os << " transfers to " << object.possible_actions.at(object.selected_action).second << '.';
    }*/
    for (int i = 0; i < (*object.possible_actions).size(); ++i) {
        os << "Satellite-KinoSat_" << (*object.possible_actions)[i].first;
        if ((*object.possible_actions)[i].second.empty())
            os << " shooting. ";
        else
            os << " transfers to " << (*object.possible_actions)[i].second << ". ";
    }
    return os;
}