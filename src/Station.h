//
// Created by wwwod on 30.11.2023.
//

#ifndef SATELLITESCHEDULE_STATION_H
#define SATELLITESCHEDULE_STATION_H

#include <iostream>
#include <vector>

class Station {
public:
    std::vector<int> visible_satellites;
    std::vector<int> possible_satellites;
    int chosen_satellite {-1};
};



#endif //SATELLITESCHEDULE_STATION_H
