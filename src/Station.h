//
// Created by wwwod on 30.11.2023.
//

#ifndef SATELLITESCHEDULE_STATION_H
#define SATELLITESCHEDULE_STATION_H

#include <iostream>
#include "Satellite.h"

class Station {
public:
    friend std::ostream& operator << (std::ostream& os, const Station& station);
    double receiveData(Satellite& satellite, std::chrono::duration<double> t);
private:
    double received = 0;
};



#endif //SATELLITESCHEDULE_STATION_H
