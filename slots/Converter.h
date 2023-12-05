//
// Created by wwwod on 01.12.2023.
//

#ifndef SATELLITESCHEDULE_CONVERTER_H
#define SATELLITESCHEDULE_CONVERTER_H

#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <stdexcept>
#include "SatelliteType.h"
namespace Converter {
    SatelliteType toSatelliteType(const std::string& id);
    std::chrono::time_point<std::chrono::system_clock> toTimePoint(const std::string& timestamp, const std::string& fmt);
}

#endif //SATELLITESCHEDULE_CONVERTER_H
