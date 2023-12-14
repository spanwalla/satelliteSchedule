//
// Created by wwwod on 09.12.2023.
//

#ifndef SATELLITESCHEDULE_OBSERVER_H
#define SATELLITESCHEDULE_OBSERVER_H

#include <string>
#include "Log/MessageType.h"

class Observer {
public:
    virtual void update(MessageType type, const std::string& message) = 0;
    virtual ~Observer() = default;
};


#endif //SATELLITESCHEDULE_OBSERVER_H
