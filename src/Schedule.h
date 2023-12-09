//
// Created by wwwod on 30.11.2023.
//

#ifndef SATELLITESCHEDULE_SCHEDULE_H
#define SATELLITESCHEDULE_SCHEDULE_H

#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include <algorithm>
#include "Event.h"
#include "Satellite.h"
#include "Station.h"
#include "Slot.h"
#include "FileWrapper.h"
#include "Converter.h"
#include "Observable.h"

class Schedule: public Observable {
public:
    explicit Schedule(const std::string& working_directory);
    void buildSchedule();
    void resetSchedule();
    [[nodiscard]] double getAllData() const;
    void addObserver(Observer* observer) override;
    void notifyObservers(MessageType type, std::string message) override;

private:
    friend class Slot;
    double all_received_data = 0;
    std::map<std::string, Satellite> satellites;
    std::map<std::string, Station> stations;
    std::vector<Event> events;
    const std::string& working_directory;
    static std::vector<std::string> ignore;
    std::vector<Observer*> observers;

    static void parseDirectory(const std::string& path, std::vector<std::string>& file_paths);
    void createEvents();
    void transformEventsToSlots();
};


#endif //SATELLITESCHEDULE_SCHEDULE_H
