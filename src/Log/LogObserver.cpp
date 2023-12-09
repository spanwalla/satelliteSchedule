//
// Created by wwwod on 09.12.2023.
//

#include "LogObserver.h"

LogObserver::LogObserver(Schedule *schedule) {
    if (schedule)
        schedule->addObserver(this);
}

void LogObserver::update(MessageType type, std::string message) {
    for (const auto& logger: loggers.at(type))
        logger->write(message);
}

void LogObserver::addLogger(MessageType type, Logger *new_logger) {
    loggers[type].push_back(new_logger);
}
