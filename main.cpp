#include <iostream>
#include "src/Satellite.h"
#include "src/Parser.h"

int main() {
    Satellite a(SatelliteType::KINO);
    Satellite b(SatelliteType::ZORKIY);
    std::chrono::duration<double> t(124.32);
    a.writeData(t);
    b.writeData(t);
    std::cout << a << '\n' << b << std::endl;
    double transferred_a = a.transferData(t);
    double transferred_b = b.transferData(t);
    std::cout << a << '\n' << b << '\n' << transferred_a << ' ' << transferred_b << std::endl;
    std::cout << a.getFreeSpace() << ' ' << b.getFreeSpace() << std::endl;
    Parser ana("DATA_Files/Facility2Constellation/Facility-Anadyr1.txt");
    std::cout << ana.parseLine() << std::endl;
    std::cout << ana.parseLine() << std::endl;
    std::cout << ana.parseLine() << std::endl;
    return 0;
}
