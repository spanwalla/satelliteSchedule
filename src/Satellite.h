//
// Created by wwwod on 16.11.2023.
//

#ifndef SATELLITESCHEDULE_SATELLITE_H
#define SATELLITESCHEDULE_SATELLITE_H

#include <iostream>
#include <chrono>
#include "SatelliteType.h"

/*
 * Класс спутника.
 * Хранит информацию о параметрах спутника (скорость передачи, количество памяти).
 * Количество информации в Гб, скорость передачи в Гбайт/c.
 * 1 Тб - 1000 Гб - 1 000 000 Мб - размер хранилища Киноспутника.
 * 0.5 Тб - 500 Гб - 500 000 Мб - размер хранилища Зоркого.
 * 4 Гбит/c - 0.5 Гб/c - 500 Мб/c - скорость заполнения памяти.
 * 1 Гбит/c - 0.125 Гб/c - 125 Мб/с - скорость сброса данных для Киноспутника.
 * 0.25 Гбит/с - 0.03125 Гб/с - 31.25 Мб/с - скорость сброса данных для Зоркого.
 */

class Satellite {
public:
    explicit Satellite(SatelliteType type);
    void writeData(std::chrono::duration<double> t);
    [[nodiscard]] double getFreeSpace() const;
    [[nodiscard]] double getFilledSpace() const;
    double transferData(std::chrono::duration<double> t);
    friend std::ostream& operator << (std::ostream& os, const Satellite& satellite);
    double transfer_speed;
private:
    double disk_space; // в Гб
    double shooting_speed;
    double filled_space;
};


#endif //SATELLITESCHEDULE_SATELLITE_H
