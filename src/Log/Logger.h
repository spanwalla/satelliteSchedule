//
// Created by wwwod on 09.12.2023.
//

#ifndef SATELLITESCHEDULE_LOGGER_H
#define SATELLITESCHEDULE_LOGGER_H

#include <string>

class Logger {
public:
    virtual void write(std::string message) = 0;
    virtual ~Logger() = default;
};


#endif //SATELLITESCHEDULE_LOGGER_H
