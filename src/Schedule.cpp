//
// Created by wwwod on 30.11.2023.
//

#include "Schedule.h"

std::vector<std::string> Schedule::ignore = {
        "readme.txt"
}; // в config

Schedule::Schedule(const std::string& working_directory) : working_directory(working_directory) {}

void Schedule::addObserver(Observer *observer) {
    observers.push_back(observer);
}

void Schedule::notifyObservers(MessageType type, const std::string& message) {
    for (Observer* observer: observers)
        observer->update(type, message);
}

void Schedule::parseDirectory(const std::string& path, std::vector<std::string>& file_paths) {
    for (auto const& entry : std::filesystem::recursive_directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt" && std::find(ignore.begin(), ignore.end(), entry.path().filename()) == ignore.end())
            file_paths.push_back(entry.path().string());
    }
}

void Schedule::buildSchedule() {
    std::stringstream ss;
    ss << "[" << std::chrono::system_clock::now() << "] START BUILDING SCHEDULE.";
    notifyObservers(MessageType::INFO, ss.str());
    createEvents();
    transformEventsToSlots();
    ss.str(std::string());
    ss.clear();
    ss << "[" << std::chrono::system_clock::now() << "] END BUILDING SCHEDULE.";
    notifyObservers(MessageType::INFO, ss.str());
}

void Schedule::createEvents() {
    std::vector<std::string> files;
    parseDirectory(working_directory, files);

    // в config
    std::regex name(R"(^(.+)-To-KinoSat_(11\d{4})$)");
    std::regex interval(R"(^\d+\s+(\d{1,2} \w{3} \d{4} \d{2}:\d{2}:\d{2}\.\d+)\s+(\d{1,2} \w{3} \d{4} \d{2}:\d{2}:\d{2}\.\d+)\s+([0-9]+\.[0-9]+)$)");
    for (const auto& filename : files) {
        FileWrapper file(filename);
        std::pair<std::string, std::string> current;
        std::stringstream ss;
        ss << "[" << std::chrono::system_clock::now() << "] READING: " << filename;
        notifyObservers(MessageType::INFO, ss.str());
        while (!file.end()) {
            std::string str = file.readLine();
            std::smatch match;
            if (std::regex_match(str, match, name)) {
                current = { match[1], match[2] };
            }
            else if (std::regex_match(str, match, interval)) {
                auto start = Converter::toTimePoint(match[1], "%d %b %Y %H:%M:%S.");
                auto end = Converter::toTimePoint(match[2], "%d %b %Y %H:%M:%S."); // формат времени в config
                if (current.first == "Russia") {
                    auto element = std::find(int_to_str_satellites.begin(), int_to_str_satellites.end(), current.second);
                    int index = std::distance(int_to_str_satellites.begin(), element);
                    if (element == int_to_str_satellites.end()) { // создать спутник, если он ещё не встречался прежде
                        int_to_str_satellites.push_back(current.second);
                        int_to_satellites.emplace_back(Converter::toSatelliteType(current.second));
                    }

                    events.emplace_back(EventType::START, start, index);
                    events.emplace_back(EventType::END, end, index);
                }
                else {
                    auto element = std::find(int_to_str_stations.begin(), int_to_str_stations.end(), current.first);
                    int index_station = std::distance(int_to_str_stations.begin(), element);
                    if (element == int_to_str_stations.end()) { // создать станцию, если она ещё не встречалась прежде
                        int_to_str_stations.push_back(current.first);
                        int_to_stations.emplace_back();
                    }

                    element = std::find(int_to_str_satellites.begin(), int_to_str_satellites.end(), current.second);
                    int index_satellite = std::distance(int_to_str_satellites.begin(), element);
                    if (element == int_to_str_satellites.end()) { // создать спутник, если он ещё не встречался прежде
                        int_to_str_satellites.push_back(current.second);
                        int_to_satellites.emplace_back(Converter::toSatelliteType(current.second));
                    }

                    events.emplace_back(EventType::START, start, index_satellite, index_station);
                    events.emplace_back(EventType::END, end, index_satellite, index_station);
                }
            }
        }
    }
    std::sort(events.begin(), events.end());
    std::stringstream ss;
    ss << "[" << std::chrono::system_clock::now() << "] Total events: " << events.size();
    notifyObservers(MessageType::INFO, ss.str());
}

void Schedule::resetSchedule() {
    int_to_str_satellites.clear();
    int_to_satellites.clear();
    int_to_str_stations.clear();
    int_to_stations.clear();
    events.clear();
}

void Schedule::transformEventsToSlots() {
    std::stringstream ss;
    ss << "[" << std::chrono::system_clock::now() << "] transformEventsToSlots started.";
    notifyObservers(MessageType::INFO, ss.str());
    Actions actions;
    if (events[0].type == EventType::START) {
        if (events[0].action.second == -1) {
            actions.shooting.push_back(events[0].action.first);
        }
        else {
            int_to_stations.at(events[0].action.second).visible_satellites.push_back(events[0].action.first);
            actions.transferring.push_back(events[0].action.second);
        }
    } // выкидывать ошибку, если первое событие конец?
    for (int i = 1; i < events.size(); ++i) {   // замена events[i] на tmp, но вроде нужен оператор копирования тогда
        if (events[i] != events[i - 1]) {
            Slot slot(events[i - 1].timestamp, events[i].timestamp, &actions, this);
            slot.makeAnotherOptimalChoice();
            notifyObservers(MessageType::SCHEDULE, slot.toString());
        }
        if (events[i].type == EventType::START) {
            if (events[i].action.second == -1) {
                actions.shooting.push_back(events[i].action.first);
            }
            else {
                int_to_stations.at(events[i].action.second).visible_satellites.push_back(events[i].action.first);
                if (std::find(actions.transferring.begin(), actions.transferring.end(), events[i].action.second) == actions.transferring.end()) {
                    actions.transferring.push_back(events[i].action.second);
                }
            }
        }
        if (events[i].type == EventType::END) {
            if (events[i].action.second == -1) {
                std::erase(actions.shooting, events[i].action.first);
            }
            else {
                std::erase(int_to_stations.at(events[i].action.second).visible_satellites, events[i].action.first);
                if (int_to_stations.at(events[i].action.second).visible_satellites.empty()) {
                    std::erase(actions.transferring, events[i].action.second);
                }
            }
        }
    }
    ss.str(std::string());
    ss.clear();
    ss << "[" << std::chrono::system_clock::now() << "] transformEventsToSlots ended.";
    notifyObservers(MessageType::INFO, ss.str());
    ss.str(std::string());
    ss.clear();
    ss << "Total: " << getAllData() << " Gb.";
    notifyObservers(MessageType::SCHEDULE, ss.str());
    notifyObservers(MessageType::INFO, ss.str());
}

double Schedule::getAllData() const {
    return all_received_data;
}