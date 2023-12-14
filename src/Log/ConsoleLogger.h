//
// Created by wwwod on 09.12.2023.
//

#ifndef SATELLITESCHEDULE_CONSOLELOGGER_H
#define SATELLITESCHEDULE_CONSOLELOGGER_H

#include <iostream>
#include "MessageType.h"
#include "Logger.h"
#include "LogObserver.h"

class ConsoleLogger: public Logger {
public:
    explicit ConsoleLogger(LogObserver* observer, const std::vector<MessageType> &subscribed);
    void write(const std::string& message) override;
};


#endif //SATELLITESCHEDULE_CONSOLELOGGER_H
