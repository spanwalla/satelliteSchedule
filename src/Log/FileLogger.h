//
// Created by wwwod on 09.12.2023.
//

#ifndef SATELLITESCHEDULE_FILELOGGER_H
#define SATELLITESCHEDULE_FILELOGGER_H

#include "../FileWrapper.h"
#include "MessageType.h"
#include "Logger.h"
#include "LogObserver.h"

class FileLogger: public Logger {
public:
    FileLogger(LogObserver* observer, const std::string& path, const std::vector<MessageType> &subscribed);
    void write(std::string message) override;
private:
    FileWrapper file;
};


#endif //SATELLITESCHEDULE_FILELOGGER_H
