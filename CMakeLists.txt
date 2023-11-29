cmake_minimum_required(VERSION 3.26)
project(satelliteSchedule)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-static")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

add_executable(satelliteSchedule main.cpp
        src/Satellite.cpp
        src/Satellite.h
        src/SatelliteType.h
        src/Parser.cpp
        src/Parser.h
)
