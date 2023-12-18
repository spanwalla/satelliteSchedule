//
// Created by wwwod on 01.12.2023.
//
#pragma warning(disable : 4996)
#include "Converter.h"

SatelliteType Converter::toSatelliteType(const std::string& satellite) {
    int id = std::stoi(satellite);
    if (id >= 110101 && id <= 110510)
        return SatelliteType::KINO;
    else if (id >= 110601 && id <= 112010)
        return SatelliteType::ZORKIY;
    throw std::invalid_argument("Invalid satellite id.");
}

std::chrono::time_point<std::chrono::system_clock> Converter::toTimePoint(const std::string& timestamp, const std::string& fmt, bool millis) {
    std::tm tm = {};
    std::istringstream ss(timestamp);
    std::string ms = "0";
    ss >> std::get_time(&tm, fmt.c_str());
    if (millis)
        ss >> ms;

    auto timePoint =
        std::chrono::system_clock::from_time_t(std::mktime(&tm)) +
        std::chrono::milliseconds(std::stoi(ms));
    return timePoint + std::chrono::seconds(-_timezone);
}