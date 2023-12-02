//
// Created by wwwod on 30.11.2023.
//

#include "Station.h"

std::ostream& operator<<(std::ostream& os, const Station& station) {
    return os << "Received: " << station.received << " Gb.";
}
