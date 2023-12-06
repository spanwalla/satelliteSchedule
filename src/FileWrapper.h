//
// Created by wwwod on 18.11.2023.
//

#ifndef SATELLITESCHEDULE_FILEWRAPPER_H
#define SATELLITESCHEDULE_FILEWRAPPER_H

#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>
#include "Slot.h"

class FileWrapper {
public:
    explicit FileWrapper(const std::string& filename, std::ios_base::openmode mode = std::ios_base::in);
    ~FileWrapper();
    std::string readLine();
    void write(const std::string& string);
    bool end();

private:
    std::fstream file;
    static std::string trim(const std::string& str); // убрать пробелы, табуляцию и перенос строк по краям строки
};


#endif //SATELLITESCHEDULE_FILEWRAPPER_H
