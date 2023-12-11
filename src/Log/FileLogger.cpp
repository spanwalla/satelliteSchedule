//
// Created by wwwod on 09.12.2023.
//

#include "FileLogger.h"

FileLogger::FileLogger(LogObserver *observer, const std::string &path, const std::vector<MessageType> &subscribed): file(path, std::ios::out) {
    for (auto type: subscribed)
        observer->addLogger(type, this);
}

void FileLogger::write(std::string message) {
    file.write(message);
}