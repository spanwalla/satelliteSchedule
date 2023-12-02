//
// Created by wwwod on 18.11.2023.
//

#ifndef SATELLITESCHEDULE_FILEWRAPPER_H
#define SATELLITESCHEDULE_FILEWRAPPER_H

#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>

class FileWrapper {
public:
    explicit FileWrapper(const std::string& filename);
    ~FileWrapper();
    std::string readLine();
    bool end();

private:
    std::ifstream file;
    static std::string trim(const std::string& str); // убрать пробелы, табуляцию и перенос строк по краям строки
};


#endif //SATELLITESCHEDULE_FILEWRAPPER_H
