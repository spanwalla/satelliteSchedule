cmake_minimum_required(VERSION 3.26)
project(satelliteSchedule)

set(CMAKE_CXX_STANDARD 20)

add_executable(satelliteSchedule main.cpp
        src/Satellite.cpp
        src/Satellite.h
        src/SatelliteType.h
        src/Parser.cpp
        src/Parser.h
)
