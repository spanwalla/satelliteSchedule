//
// Created by wwwod on 30.11.2023.
//

#include "Station.h"

std::ostream& operator<<(std::ostream& os, const Station& station) {
    return os << "Received: " << station.received << " Gb.";
}

double Station::receiveData(Satellite& satellite, std::chrono::duration<double> t) {
    double received_on_slot = satellite.transferData(t);
    received += received_on_slot;
    return received_on_slot;
}