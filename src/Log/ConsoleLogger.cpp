//
// Created by wwwod on 09.12.2023.
//

#include "ConsoleLogger.h"

ConsoleLogger::ConsoleLogger(LogObserver *observer, const std::vector<MessageType>& subscribed) {
    for (auto type: subscribed)
        observer->addLogger(type, this);
}

void ConsoleLogger::write(const std::string& message) {
    std::cout << message << std::endl;
}
