//
// Created by wwwod on 16.11.2023.
//

#include "Satellite.h"

Satellite::Satellite(SatelliteType type) : shooting_speed(SHOOTING_SPEED), filled_space(0) {
    switch (type) {
    case SatelliteType::KINO:
        disk_space = KINO_SPACE;
        transfer_speed = KINO_TRANSFER_SPEED;
        break;

    case SatelliteType::ZORKIY:
        disk_space = ZORKIY_SPACE;
        transfer_speed = ZORKIY_TRANSFER_SPEED;
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

double Satellite::transferData(std::chrono::duration<double> t) {
    double to_transfer = t.count() * transfer_speed;
    if (filled_space - to_transfer < 0) {
        to_transfer = filled_space;
        filled_space = 0;
    }
    else
        filled_space -= to_transfer;
    return to_transfer;
}

double Satellite::getTransferSpeed() const {
    return transfer_speed;
}
