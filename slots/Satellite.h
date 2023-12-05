//
// Created by wwwod on 16.11.2023.
//

#ifndef SATELLITESCHEDULE_SATELLITE_H
#define SATELLITESCHEDULE_SATELLITE_H

#include <iostream>
#include <chrono>
#include "SatelliteType.h"

/*
 *  ласс спутника.
 * ’ранит информацию о параметрах спутника (скорость передачи, количество пам€ти).
 *  оличество информации в √б, скорость передачи в √байт/c.
 * 1 “б - 1000 √б - 1 000 000 ћб - размер хранилища  иноспутника.
 * 0.5 “б - 500 √б - 500 000 ћб - размер хранилища «оркого.
 * 4 √бит/c - 0.5 √б/c - 500 ћб/c - скорость заполнени€ пам€ти.
 * 1 √бит/c - 0.125 √б/c - 125 ћб/с - скорость сброса данных дл€  иноспутника.
 * 0.25 √бит/с - 0.03125 √б/с - 31.25 ћб/с - скорость сброса данных дл€ «оркого.
 */

class Satellite {
public:
    explicit Satellite(SatelliteType type);
    void writeData(std::chrono::duration<double> t);
    [[nodiscard]] double getFreeSpace() const;
    double transferData(std::chrono::duration<double> t);
    friend std::ostream& operator << (std::ostream& os, const Satellite& satellite);

private:
    double disk_space; // в √б
    double shooting_speed;
    double transfer_speed;
    double filled_space;
};


#endif //SATELLITESCHEDULE_SATELLITE_H
