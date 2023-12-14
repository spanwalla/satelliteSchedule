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
    explicit FileWrapper(const std::string& filename, std::ios_base::openmode mode = std::ios_base::in);
    ~FileWrapper();
    std::string readLine();
    void write(const std::string& string);
    bool end();

private:
    std::fstream file;
    static std::string trim(const std::string& str); // убрать табуляцию, обрезать пробелы справа и слева
};


#endif //SATELLITESCHEDULE_FILEWRAPPER_H
