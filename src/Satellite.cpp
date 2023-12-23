//
// Created by wwwod on 16.11.2023.
//

#include "Satellite.h"

Satellite::Satellite(SatelliteType type) : shooting_speed(SHOOTING_SPEED), filled_space(0) {
    switch (type) {
    case SatelliteType::KINO:
        disk_space = KINO_SPACE;
            transmit_speed = KINO_TRANSMITTER_SPEED;
        break;

    case SatelliteType::ZORKIY:
        disk_space = ZORKIY_SPACE;
            transmit_speed = ZORKIY_TRANSMITTER_SPEED;
        break;
    }
}

void Satellite::writeData(std::chrono::duration<double> t) {
    filled_space += t.count() * shooting_speed;
    if (filled_space > disk_space)
        filled_space = disk_space;
}

double Satellite::getFilledSpace() const {
    return filled_space;
}

double Satellite::transmitData(std::chrono::duration<double> t) {
    double to_transmitting = t.count() * transmit_speed;
    if (filled_space - to_transmitting < 0) {
        to_transmitting = filled_space;
        filled_space = 0;
    }
    else
        filled_space -= to_transmitting;
    return to_transmitting;
}

double Satellite::getTransmitterSpeed() const {
    return transmit_speed;
}

bool Satellite::hasFreeSpace() const {
    return filled_space < disk_space;
}
