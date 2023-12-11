//
// Created by wwwod on 30.11.2023.
//

#ifndef SATELLITESCHEDULE_STATION_H
#define SATELLITESCHEDULE_STATION_H

#include <iostream>
#include <vector>

class Station {
public:
    friend std::ostream& operator << (std::ostream& os, const Station& station);
    std::vector<std::string> visible_satellites;
    std::vector<int> possible_satellites;
    std::string chosen_satellite;
};



#endif //SATELLITESCHEDULE_STATION_H
