//
// Created by wwwod on 09.12.2023.
//

#ifndef SATELLITESCHEDULE_OBSERVABLE_H
#define SATELLITESCHEDULE_OBSERVABLE_H

#include <string>
#include <vector>
#include "Observer.h"
#include "Log/MessageType.h"

class Observable {
public:
    virtual void addObserver(Observer* observer) = 0;
    virtual void notifyObservers(MessageType type, const std::string& message) = 0;
    virtual ~Observable() = default;
};


#endif //SATELLITESCHEDULE_OBSERVABLE_H
