cmake_minimum_required(VERSION 3.22.1)
project(satelliteSchedule)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-static")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

add_executable(satelliteSchedule main.cpp
        src/Satellite.cpp
        src/Satellite.h
        src/SatelliteType.h
        src/FileWrapper.cpp
        src/FileWrapper.h
        src/Event.cpp
        src/Event.h
        src/EventType.h
        src/Station.h
        src/Schedule.cpp
        src/Schedule.h
        src/Converter.cpp
        src/Converter.h
        src/Slot.cpp
        src/Slot.h
        src/Observable.h
        src/Observer.h
        src/Log/MessageType.h
        src/Log/LogObserver.cpp
        src/Log/LogObserver.h
        src/Log/Logger.h
        src/Log/ConsoleLogger.cpp
        src/Log/ConsoleLogger.h
        src/Log/FileLogger.cpp
        src/Log/FileLogger.h
)
