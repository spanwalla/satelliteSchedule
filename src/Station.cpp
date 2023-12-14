//
// Created by wwwod on 30.11.2023.
//

#include "Station.h"

std::ostream& operator<<(std::ostream& os, const Station& station) {
    return os << "get from: " << station.chosen_satellite;
}
