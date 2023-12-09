//
// Created by wwwod on 09.12.2023.
//

#ifndef SATELLITESCHEDULE_LOGOBSERVER_H
#define SATELLITESCHEDULE_LOGOBSERVER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "../Observer.h"
#include "Logger.h"
#include "../Schedule.h"

class LogObserver: public Observer {
public:
    explicit LogObserver(Schedule* schedule);
    void update(MessageType type, std::string message) override;
    void addLogger(MessageType type, Logger* new_logger);
private:
    std::unordered_map<MessageType, std::vector<Logger*>> loggers;
};


#endif //SATELLITESCHEDULE_LOGOBSERVER_H
