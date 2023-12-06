#include <iostream>
#include "src/Schedule.h"

int main() {
    // FileWrapper ana("DATA_Files/Facility2Constellation/Facility-Anadyr1.txt");
    // std::regex name(R"(^(.+)-To-KinoSat_(11\d{4})$)");
    // std::regex interval(R"(^\d+\s+(\d{1,2} \w{3} \d{4} \d{2}:\d{2}:\d{2}\.\d+)\s+(\d{1,2} \w{3} \d{4} \d{2}:\d{2}:\d{2}\.\d+)\s+([0-9]+\.[0-9]+)$)");

    std::cout << "[" << std::chrono::system_clock::now() << "] Program started.\n";
    Schedule schedule("DATA_Files", "result.txt");
    schedule.buildSchedule();
    std::cout << "[" << std::chrono::system_clock::now() << "] Program ended.\n";
    std::cout << "Total, Gb: " << schedule.getAllData() << std::endl;
    return 0;
}