//
// Created by wwwod on 01.12.2023.
//

#include "Slot.h"

Slot::Slot(Schedule* schedule, std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end): schedule(schedule), interval(std::make_pair(start, end)) {
    if (interval.first >= interval.second)
        throw std::invalid_argument("End of slot is earlier than start.");
    // добавить инициализацию доступных действий
}

void Slot::makeNotOptimalChoose() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, int(possible_actions.size()));
    selected_action = dist(gen);
}

std::ostream& operator<<(std::ostream &os, const Slot &object) {

    os << "[" << object.interval.first << ", " << object.interval.second << "] Action: ";
    if (object.selected_action == -1)
        os << "not chosen.";
    else {
        os << "Satellite-KinoSat_" << object.possible_actions.at(object.selected_action).first;
        if (object.possible_actions.at(object.selected_action).second.empty())
            os << " shooting.";
        else
            os << " transfers to " << object.possible_actions.at(object.selected_action).second << '.';
    }
    return os;
}


