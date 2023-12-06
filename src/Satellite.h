//
// Created by wwwod on 16.11.2023.
//

#ifndef SATELLITESCHEDULE_SATELLITE_H
#define SATELLITESCHEDULE_SATELLITE_H

#include <iostream>
#include <chrono>
#include "SatelliteType.h"

/*
 * ����� ��������.
 * ������ ���������� � ���������� �������� (�������� ��������, ���������� ������).
 * ���������� ���������� � ��, �������� �������� � �����/c.
 * 1 �� - 1000 �� - 1 000 000 �� - ������ ��������� ������������.
 * 0.5 �� - 500 �� - 500 000 �� - ������ ��������� �������.
 * 4 ����/c - 0.5 ��/c - 500 ��/c - �������� ���������� ������.
 * 1 ����/c - 0.125 ��/c - 125 ��/� - �������� ������ ������ ��� ������������.
 * 0.25 ����/� - 0.03125 ��/� - 31.25 ��/� - �������� ������ ������ ��� �������.
 */

class Satellite {
public:
    explicit Satellite(SatelliteType type);
    void writeData(std::chrono::duration<double> t);
    [[nodiscard]] double getFreeSpace() const;
    double transferData(std::chrono::duration<double> t);
    friend std::ostream& operator << (std::ostream& os, const Satellite& satellite);

private:
    double disk_space; // � ��
    double shooting_speed;
    double transfer_speed;
    double filled_space;
};


#endif //SATELLITESCHEDULE_SATELLITE_H
