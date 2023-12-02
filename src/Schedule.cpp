//
// Created by wwwod on 30.11.2023.
//

#include "Schedule.h"

std::vector<std::string> Schedule::ignore = {
        "readme.txt"
}; // в config

Schedule::Schedule(const std::string& working_directory): working_directory(working_directory) {}



void Schedule::parseDirectory(const std::string &path, std::vector<std::string>& file_paths) {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt" && std::find(ignore.begin(), ignore.end(), entry.path().filename()) == ignore.end())
            file_paths.push_back(entry.path().string());
    }
}

void Schedule::buildSchedule() {
    createEvents();
    transformEventsToSlots();
}

void Schedule::createEvents() {
    std::vector<std::string> files;
    parseDirectory(working_directory, files);

    // в config
    std::regex name(R"(^(.+)-To-KinoSat_(11\d{4})$)");
    std::regex interval(R"(^\d+\s+(\d{1,2} \w{3} \d{4} \d{2}:\d{2}:\d{2}\.\d+)\s+(\d{1,2} \w{3} \d{4} \d{2}:\d{2}:\d{2}\.\d+)\s+([0-9]+\.[0-9]+)$)");
    for (const auto& filename: files) {
        FileWrapper file(filename);
        std::pair<std::string, std::string> current;
        std::cout << filename << std::endl;
        while (!file.end()) {
            std::string str = file.readLine();
            std::smatch match;
            if (std::regex_match(str, match, name)) {
                current = {match[1], match[2]};
            } else if (std::regex_match(str, match, interval)) {
                auto start = Converter::toTimePoint(match[1], "%d %b %Y %H:%M:%S.");
                auto end = Converter::toTimePoint(match[2], "%d %b %Y %H:%M:%S."); // формат времени в config
                if (current.first == "Russia") {
                    if (!satellites.contains(current.second))
                        satellites.emplace(current.second, Satellite(Converter::toSatelliteType(current.second)));

                    events.emplace_back(EventType::START, start, current.second);
                    events.emplace_back(EventType::END, end, current.second);
                } else {
                    if (!stations.contains(current.first))
                        stations.emplace(current.first, Station());
                    if (!satellites.contains(current.second))
                        satellites.emplace(current.second, Satellite(Converter::toSatelliteType(current.second)));

                    events.emplace_back(EventType::START, start, current.second, current.first);
                    events.emplace_back(EventType::END, end, current.second, current.first);
                }
            }
        }
    }
    std::sort(events.begin(), events.end());
}

Satellite& Schedule::getSatellite(const std::string& id) {
    return satellites.at(id);
}

Station& Schedule::getStation(const std::string &name) {
    return stations.at(name);
}

void Schedule::resetSchedule() {
    stations.clear();
    satellites.clear();
    events.clear();
    slots.clear();
}

void Schedule::transformEventsToSlots() {
    std::vector<std::pair<std::string, std::string>> actions;

    for (int i = 0; i < events.size() - 1; ++i) {
        // сюда логику обработки последовательности событий
    }
}
