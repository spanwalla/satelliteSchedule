#include <iostream>
#include "Schedule.h"

int main() {
    // FileWrapper ana("DATA_Files/Facility2Constellation/Facility-Anadyr1.txt");
    // std::regex name(R"(^(.+)-To-KinoSat_(11\d{4})$)");
    // std::regex interval(R"(^\d+\s+(\d{1,2} \w{3} \d{4} \d{2}:\d{2}:\d{2}\.\d+)\s+(\d{1,2} \w{3} \d{4} \d{2}:\d{2}:\d{2}\.\d+)\s+([0-9]+\.[0-9]+)$)");

    Schedule schedule("DATA_Files");
    schedule.buildSchedule();
    std::cout << schedule.getAllData() << std::endl;
    return 0;
}